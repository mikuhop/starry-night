/**
 * @file   chef_wait_event_counter.h/chef_wait_event_counter.cc
 * @deps   chef_env.hpp/chef_noncopyable.hpp
 *
 * @author
 *   chef <191201771@qq.com>
 *     -initial release xxxx-xx-xx
 *
 * @brief
 *   -阻塞等待1~N个事件发生。
 *   -也可选择设置超时时间，到达后不再阻塞。
 *   -使用者不用关心cv、mutex等线程同步实现的细节~
 *
 */

#ifndef _CHEF_BASE_WAIT_EVENT_COUNTER_H_
#define _CHEF_BASE_WAIT_EVENT_COUNTER_H_

#include "chef_noncopyable.hpp"
#include "chef_env.hpp"

namespace chef {

  class wait_event_counter : public chef::noncopyable {
    public:
      /**
       * @param need_count 需要notify多少次，wait才能通过
       *
       */
      explicit wait_event_counter(int need_count=1);

      ~wait_event_counter();

      /// notify调用发生在wait执行前或wait中，都有效~
      void notify();

      /// 阻塞直到构造函数中指定的<need_count>次notify已发生。
      void wait();

      /**
       * 阻塞直到构造函数中指定的<need_count>次notify已发生或超时。
       *
       * @param timeout_ms 超时时间，单位毫秒，如果设置为0，则无超时机制。
       *
       * @return
       *   true  通知达成
       *   false 超时达成
       *
       */
      bool wait_for(uint32_t timeout_ms);

    private:
      bool check_();

    private:
      const int                need_count_;
      chef::atomic<int>        counted_;
      chef::mutex              mutex_;
      chef::condition_variable cond_;
  };

} // namespace chef

#endif // _CHEF_BASE_WAIT_EVENT_COUNTER_H_