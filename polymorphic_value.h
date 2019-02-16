#pragma once
#include <utility>
#include <memory>
#include <algorithm>
#include <variant>
#include <vector>

static constexpr int min_sbo_size = sizeof(int*) * 2;//unique_ptr + vtable

template<typename base,int sbo_size = 64>
struct polymorphic_value{
	//static_assert(std::is_same_v<std::decay_t<base>,base>);
	static_assert(sbo_size >= min_sbo_size);
	
	polymorphic_value()noexcept {
		new(&m_storage) no_type{};
	};

	template<typename D,std::enable_if_t<std::is_base_of_v<base,D>,int> = 0>
	polymorphic_value(D d) {
		create<std::decay_t<D>>(std::move(d));
	}

	template<typename O, std::enable_if_t<std::is_base_of_v<base, O>,int> = 0>
	polymorphic_value(const polymorphic_value<O>& other) {
		other.me().clone(m_storage);
	}
	
	template<typename O, std::enable_if_t<
		std::is_base_of_v<base, O> &&
		!std::is_same_v<O, polymorphic_value>, int> = 0
	>
		polymorphic_value(polymorphic_value<O>&& other) {
		other.me().move(m_storage);		
	}

	polymorphic_value(polymorphic_value&& other)noexcept {
		other.me().move(m_storage);
	}

	polymorphic_value(const polymorphic_value& other){
		other.me().clone(m_storage);
	}
	/*
	template<typename O,int sbo_size2,std::enable_if_t<
		!std::is_same_v<O,base> && sbo_size2!=sbo_size,int> = 0
	>
	polymorphic_value(const polymorphic_value<O,sbo_size2>& other) {
		other.me().clone(&m_storage, sbo_size);
	}

	template<typename O, int sbo_size2, std::enable_if_t<
		!std::is_same_v<O, base> && sbo_size2 != sbo_size, int> = 0
	>
	polymorphic_value(polymorphic_value<O, sbo_size2>&& other) {
		other.me().move(&m_storage, sbo_size);
	}
	*/
	template<
		typename D,
		std::enable_if_t<
		std::is_base_of_v<base, D> &&
		!std::is_same_v<D, polymorphic_value>, int
	> = 0>
	polymorphic_value& operator=(D d) {
		destroy();
		create<D>(std::move(d));
		return *this;
	}

	polymorphic_value& operator=(polymorphic_value&& other)noexcept {
		destroy();
		other.me().move(m_storage);
		return *this;
	}

	polymorphic_value& operator=(const polymorphic_value& other) {
		destroy();
		other.me().clone(m_storage);
		return *this;
	}

	template<
		typename D, typename decayed_type = std::decay_t<D>,
		std::enable_if_t<
		std::is_base_of_v<base, decayed_type> &&
		!std::is_same_v<decayed_type, polymorphic_value>, int
	> = 0>
	polymorphic_value& operator=(D&& d) {
		destroy();
		create<std::decay_t<D>>(std::forward<D>(d));
		return *this;
	}

	template<typename O, std::enable_if_t<
		std::is_base_of_v<base, O> &&
		!std::is_same_v<O, polymorphic_value>, int
	> = 0>
	polymorphic_value& operator=(const polymorphic_value<O,sbo_size>& other) {
		destroy();
		other.me().clone(m_storage);
		return *this;
	}
	/*
	template<typename O, int sbo_size2, std::enable_if_t<
		!std::is_same_v<O, base> && sbo_size2 != sbo_size
	, int> = 0>
	polymorphic_value& operator=(const polymorphic_value<O, sbo_size2>& other) {
		destroy();
		other.me().clone(&m_storage, sbo_size);
		return *this;
	}

	template<typename O, int sbo_size2, std::enable_if_t<
		!std::is_same_v<O, base> && sbo_size2 != sbo_size
	, int> = 0>
	polymorphic_value& operator=(polymorphic_value<O, sbo_size2>&& other) {
		destroy();
		other.me().move(&m_storage, sbo_size);
		return *this;
	}
	*/
	~polymorphic_value() {
		destroy();
	}

	base& operator*() {
		return me().get();
	}

	const base& operator*() const {
		return me().get();
	}

	base& get() {
		return me().get();
	}

	const base& get() const {
		return me().get();
	}


	base* operator->() {
		return &me().get();
	}

	const base* operator->() const {
		return &me().get();
	}

	operator base&(){
		return me().get();
	}

	operator const base&() const{
		return me().get();
	}

	void reset() {
		destroy();
		new(&m_storage) no_type;
	}

	explicit operator bool()const {
		return me().rename_me();
	}

private:
	void destroy() const{
		std::destroy_at(&me());
	}

	struct concept_{// NOLINT
		virtual ~concept_() = default;
		virtual base& get() = 0;
		virtual void clone(std::aligned_storage_t<sbo_size>&) = 0;
		virtual void move(std::aligned_storage_t<sbo_size>&) = 0;

		virtual bool rename_me()const noexcept {
			return true;
		}	
	};

	template<typename derived>
	struct model_sso :concept_ {
		model_sso() = default;

		template<typename ...T>
		model_sso(T&&... t):d(std::forward<T>(t)...) {}

		base& get()override final {
			return d;
		}
		void clone(std::aligned_storage_t<sbo_size>& storage)override final {
			new(&storage) model_sso<derived>(d);
		}
		void move(std::aligned_storage_t<sbo_size>& storage)override final {
			new(&storage) model_sso<derived>(std::move(d));
		}
		/*
		void clone(void* where, int size)override final {
			clone_to(d, where, size);
		}

		void move(void* where, int size)override final {
			move_to(d, where, size);
		}*/

		derived d;
	};

	template<typename derived>
	struct model_not_sso :concept_ {
		model_not_sso() = default;

		template<typename ...T>
		model_not_sso(T&&... t) :ptr(std::make_unique<derived>(std::forward<T>(t)...)) {}

		base& get()override final {
			return *ptr;
		}

		void clone(std::aligned_storage_t<sbo_size>& storage)override final {
			new(&storage) model_not_sso<derived>(*ptr);
		}

		void move(std::aligned_storage_t<sbo_size>& storage)override final {
			new(&storage) model_not_sso<derived>(std::move(*ptr));
		}
		/*
		void clone(void* where, int size)override final {
			clone_to(*ptr, where, size);
		}

		void move(void* where, int size)override final {
			move_to(*ptr, where, size);
		}
		*/
		std::unique_ptr<derived> ptr;
	};

	struct no_type:concept_{
		base& get()override final {
			//throw std::runtime_error(";-;");
			std::terminate();
		}
		void clone(std::aligned_storage_t<sbo_size>&)override final { }

		void move(std::aligned_storage_t<sbo_size>&)override final { }
		/*
		void clone(void*, int)override final { }

		void move(void*, int)override final { }
		*/
		bool rename_me()const noexcept final{
			return false;
		}
	};

	template<typename D,typename ...Args>
	void create(Args&&... args) {
		if constexpr(sizeof(model_sso<D>)<=sbo_size){
			new(&m_storage) model_sso<D>(std::forward<Args>(args)...);
		}else {
			new(&m_storage) model_not_sso<D>(std::forward<Args>(args)...);
		}
	}

	concept_& me() const noexcept{
		return *(concept_*)(std::launder(&m_storage));
	}

	std::aligned_storage_t<sbo_size> m_storage{};

	template<typename,int>
	friend struct polymorphic_value;
};
