/* -*- C -*- */
/*
 * Copyright (c) 2013-2020 Seagate Technology LLC and/or its Affiliates
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For any questions about this software or licensing,
 * please email opensource@seagate.com or cortx-questions@seagate.com.
 *
 */

#pragma once

#ifndef __MOTR___DTM0_NET_H__
#define __MOTR___DTM0_NET_H__

#include "fid/fid.h" /* m0_fid */

/**
 * @defgroup dtm0
 *
 * @{
 */

/*
 * Use-cases and examples:
 *
 * net.send:
 *	coro {
 *		struct msg { txd, ... };
 *		dnet = &dod->dod_net;
 *		buf = { &msg, sizeof(msg) };
 *		target = txd.participants[N];
 *		tag = PERSISTENT
 *		m0_dtm0_net_send(dnet, target, buf, tag, op);
 *		await(op);
 *	}
 * net.recv:
 *	coro {
 *		be_op op;
 *		buf buf;
 *		msg msg;
 *		fid source;
 *		activate(op);
 *		tag = PERSISTENT;
 *		m0_dtm0_net_recv(dnet, &fid, &buf, &op);
 *		await(op);
 *		copy(msg, buf.addr, buf.size);
 *		handle(source, msg);
 *	}
 */

/* import */
struct m0_be_op;
struct m0_buf;

struct m0_dtm0_net_cfg {
	struct m0_fid dnc_instance_fid;
	uint64_t      dnc_inflight_max_nr;
	uint32_t      dnc_tags_max_nr;
};


struct m0_dtm0_net {
	struct m0_dtm0_net_cfg dnet_cfg;
};

M0_INTERNAL int m0_dtm0_net_init(struct m0_dtm0_net     *dnet,
				 struct m0_dtm0_net_cfg *dnet_cfg);
M0_INTERNAL void m0_dtm0_net_fini(struct m0_dtm0_net  *dnet);

M0_INTERNAL void m0_dtm0_net_send(struct m0_dtm0_net       *dnet,
				  const struct m0_fid      *target,
				  const struct m0_buf      *msg,
				  uint32_t                  tag,
				  struct m0_be_op          *op);

M0_INTERNAL void m0_dtm0_net_recv(struct m0_dtm0_net       *dnet,
				  struct m0_fid            *source,
				  struct m0_buf            *msg,
				  uint32_t                  tag,
				  struct m0_be_op          *op);


/** @} end of dtm0 group */
#endif /* __MOTR___DTM0_NET_H__ */

/*
 *  Local variables:
 *  c-indentation-style: "K&R"
 *  c-basic-offset: 8
 *  tab-width: 8
 *  fill-column: 80
 *  scroll-step: 1
 *  End:
 */
/*
 * vim: tabstop=8 shiftwidth=8 noexpandtab textwidth=80 nowrap
 */
