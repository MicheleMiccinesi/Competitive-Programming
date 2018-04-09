/* Another small exercise: thread safe queue using shared_mutexes */
/* License Info: contact Michele Miccinesi                        */

#include <queue>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <memory>

template <class T, class Container = std::queue<T>>
class safe_queue{
	Container _Q;
	mutable std::condition_variable_any _cv;
	mutable std::shared_mutex mut;
public:
	safe_queue(const safe_queue& queue){
		std::unique_lock<std::shared_mutex> lk(queue.mut);
		_Q = queue._Q;
	}
	safe_queue(): _Q(){}

	bool try_pop(T& var){
		std::unique_lock<std::shared_mutex> lk(mut);
		if( _Q.empty() )
			return false;
		var = _Q.front();
		_Q.pop();
		return true;
	}
	std::shared_ptr<T> try_pop(){
		std::unique_lock<std::shared_mutex> lk(mut);
		if( _Q.empty() )
			return std::make_shared<T> ();
		std::shared_ptr<T> sptr( std::make_shared<T>(_Q.front()) );
		_Q.pop();
		return sptr;
	}
	void wait_pop(T& var){
		std::unique_lock<std::shared_mutex> lk(mut);
		_cv.wait(lk, [this]{ return !_Q.empty(); } );
		var = std::move(_Q.front());
		_Q.pop();
	}
	std::shared_ptr<T> wait_pop(){
		std::unique_lock<std::shared_mutex> lk(mut);
		_cv.wait(lk, [this]{ return !_Q.empty(); } );
		std::shared_ptr<T> sptr( std::make_shared<T> (_Q.front()) );
		_Q.pop();
		return sptr;
	}
	void push(T&& val){
		std::lock_guard<std::shared_mutex> lk(mut);
		_Q.emplace(std::forward(val));
		_cv.notify_one();
	}
	void push(const T& val){
		std::lock_guard<std::shared_mutex> lk(mut);
		_Q.push(val);
		_cv.notify_one();
	}
	bool empty() const{
		std::shared_lock<std::shared_mutex> slk(mut);
		return _Q.empty();
	}
	int size() const{
		std::shared_lock<std::shared_mutex> slk(mut);
		return _Q.size();
	}
	std::shared_ptr<T> front() const{
		std::shared_lock<std::shared_mutex> slk(mut);
		return _Q.empty()?std::make_shared<T>() : std::make_shared<T>(_Q.front());
	}
};
