/* SPDX-License-Identifier: MIT */
/*
 * Copyright (c) 2025 HiSilicon Technologies Co., Ltd. All rights reserved.
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 */

#ifndef __U_UTOOL_DEBUGFS_H__
#define __U_UTOOL_DEBUGFS_H__

#include "u_utool_fwctl.h"
#include "u_utool_common.h"


struct list_head {
	struct list_head *next, *prev;
};

static inline void __list_add(struct list_head *tmp,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = tmp;
	tmp->next = next;
	tmp->prev = prev;
	prev->next = tmp;
}

static inline void list_add(struct list_head *tmp, struct list_head *head)
{
	__list_add(tmp, head, head->next);
}

static inline void list_add_tail(struct list_head *tmp, struct list_head *head)
{
	__list_add(tmp, head->prev, head);
}

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

static inline void list_del(struct list_head *entry)
{
	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
	entry->next = NULL;
	entry->prev = NULL;
}

#define list_entry(LINK, TYPE, MEMBER) \
	((TYPE *)((char *)(LINK)-(uint64_t)(&((TYPE *)0)->MEMBER)))

#define list_first_entry(PTR, TYPE, MEMBER) \
	list_entry((PTR)->next, TYPE, MEMBER)

#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_for_each_entry(POS, HEAD, MEMBER)				\
	for ((POS) = list_first_entry(HEAD, typeof(*(POS)), MEMBER);	\
	     &(POS)->MEMBER != (HEAD);					\
	     (POS) = list_next_entry(POS, MEMBER))

#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
	     n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))

int utool_debugfs_cmd_dispatch(struct utool_dev *dev, struct utool_cmd_param *param);

#endif
