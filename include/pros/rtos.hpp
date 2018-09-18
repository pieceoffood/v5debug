/**
 * @Author: 陈昱安
 * @Date:   2018-09-16T00:20:57+08:00
 * @Email:  31612534@qq.com
 * @Last modified by:   陈昱安
 * @Last modified time: 2018-09-18T21:49:48+08:00
 */

/**
 * \file pros/rtos.hpp
 *
 * Contains declarations for the PROS RTOS kernel for use by typical VEX
 * programmers.
 *
 * Visit https://pros.cs.purdue.edu/v5/tutorials/topical/multitasking.html to
 * learn more.
 *
 * This file should not be modified by users, since it gets replaced whenever
 * a kernel upgrade occurs.
 *
 * Copyright (c) 2017-2018, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_RTOS_HPP_
#define _PROS_RTOS_HPP_

#include "pros/rtos.h"
#undef delay
#include <cstdint>
#include <cstdlib>

namespace pros
{
class Task
{
  public:
    /**
 * 创建一个新线程并将其添加到准备运行的线程列表中。
 * @param function    指向线程输入函数的指针
 * @param parameters  指向内存的指针，用作正在创建的任务的参数。此内存通常不应来自堆栈，而应来自动态（即malloc'd）或静态分配的内存。
 * @param prio        任务应该运行的优先级。通常使用TASK_PRIORITY_DEFAULT 加/减1或2。
 * @param stack_depth 堆栈深度,任务上可用的单词数（即4×StktAsHead）堆栈。TASK_STACK_DEPTH_DEFAULT通常就足够的。
 * @param name        任务的描述性名称。这主要是为了方便调试。这个名字可以长达32个字符。
 */
    Task(task_fn_t function, void *parameters = NULL, std::uint32_t prio = TASK_PRIORITY_DEFAULT,
         std::uint16_t stack_depth = TASK_STACK_DEPTH_DEFAULT, const char *name = "");
    /**
 * 从已使用C API创建的任务创建Task对象。
 * @param task 要为其创建对象的任务
 */
    Task(task_t task);

    /**
 * 运算符重载,要为其创建对象的任务
 * @return  [description]
 */
    void operator=(const task_t in);
    /**
 *获得指定任务的优先级。
 * @return  任务的优先级。
 */
    std::uint32_t get_priority(void);
    /**
 * 重新设置当前线程的优先级,如果指定任务的状态可用于调度（例如，未阻止）并且新优先级高于当前运行的任务，则可能发生上下文切换。
 * @param prio 任务的新优先级
 */
    void set_priority(std::uint32_t prio);
    /**
 * 返回指定任务的状态。
 * @return  任务的状态。（见task_state_e_t）。
 */
    std::uint32_t get_state(void);

    /**
 * 暂停当前线程
 */
    void suspend(void);

    /**
 * 恢复当前线程
 */
    void resume(void);

    /**
 * 获取当前线程的名称
 * @return  返回线程的名称
 */
    const char *get_name(void);
    /**
 * 向任务发送简单通知并递增通知计数器。
 * @return  返回始终为true。
 */
    std::uint32_t notify(void);

    /**
 * 向任务发送通知，可选择执行某些操作。在修改通知值之前，还将检索目标任务中的通知值。
 * @param  value      执行操作时使用的值
 * @param  action     可选地执行任务通知的操作
 * @param  prev_value 存储目标任务的通知的先前值的指针可以是NULL
 * @return            取决于通知操作。对于NOTIFY_ACTION_NO_OWRITE：如果可以在不需要覆盖的情况下写入值，则返回0，
 * 						否则返回1。对于所有其他NOTIFY_ACTION值：始终返回0
  	*/
    std::uint32_t notify_ext(std::uint32_t value, notify_action_e_t action, std::uint32_t *prev_value);

    /**
 * 等待通知非零。
 * @param  clear_on_exit 如果为真（1），则清除通知值。如果为false（0），则通知值递减。
 * @param  timeout       指定等待通知发生的时间。
 * @return               递减或清除任务的通知值之前的值。
 */
    std::uint32_t notify_take(bool clear_on_exit, std::uint32_t timeout);

    /**
 * 清除任务通知。
 * @return  如果没有等待通知则返回 False，如果有，则返回 true
 */
    bool notify_clear(void);

    /**
 * 将任务延迟给定的毫秒数。这不是使任务以预定义的间隔执行代码的最佳方法，
 * 因为延迟时间是从请求延迟时开始测量的。要循环延迟，请使用delay_until。
 * @param milliseconds 等待的时间,单位是毫秒
 */
    static void delay(const std::uint32_t milliseconds);

    /**
 * 将任务延迟到指定时间。周期性任务可以使用此功能来确保恒定的执行频率。
 * 该任务将在当时被唤醒，并将更新以反映任务将解除阻止的时间。*prev_time + delta*prev_time
 * @param prev_time 指向存储设定点时间的位置的指针
 * @param delta     等待的毫秒数（每秒1000毫秒）
 */
    static void delay_until(std::uint32_t *const prev_time, const std::uint32_t delta);
    /**
 * 返回内核当前正在管理的任务数，包括所有就绪，阻止或挂起的任务。
 * 已被删除但尚未被空闲任务获取的任务也将包含在计数中。最近创建的任务可能需要计算一个上下文切换。
 * @return  内核当前正在管理的任务数
 */
    static std::uint32_t get_count(void);

  private:
    task_t task;
};

class Mutex
{
  public:
    /**
	   * 互斥锁
	   */
    Mutex(void);
    /**
 * 取出并锁定互斥锁，在超时之前等待一定的毫秒数。
 * @param  timeout 在互斥锁可用之前等待的时间。超时0可用于轮询互斥锁。TIMEOUT_MAX可用于无限期阻止。
 * @return        如果成功获取互斥锁，则返回 true，否则返回 false。如果返回false，则errno设置一个提示，说明无法获取互斥锁的原因。
 */
    bool take(std::uint32_t timeout);

    /**
 * 解锁互斥锁。
 * @return  返回：如果成功返回互斥锁，则返回true，否则返回false。如果返回false，则errno设置一个提示，说明无法返回互斥锁的原因。
 */
    bool give(void);

  private:
    mutex_t mutex;
};

using pros::c::millis;

using pros::c::delay;
} // namespace pros

#endif // _PROS_RTOS_HPP_s
