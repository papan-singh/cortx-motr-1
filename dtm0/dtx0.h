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

#ifndef __MOTR___DTM0_DTX0_H__
#define __MOTR___DTM0_DTX0_H__

#include "sm/sm.h" /* m0_sm */

/**
 * @defgroup dtm0
 *
 * @{
 */

/*
 * DTX use-cases and examples
 *
 * dtx.client.init:
 *   dtx = &m0_op->dtx;
 *   m0_dtx0_init(dtx, m0c->dod);
 *   m0_dtx0_timestamp_set(dtx);
 *   fids = { cas2dtm(cas_req[0]->target), ... };
 *   fids_nr = nr_of_involved_targets (including transient targets);
 *   m0_dtx0_participants_set(dtx, fids, fids_nr);
 *   m0_dtx0_buf_set(dtx, serialised(cas_req[0]->cas_op));
 *   m0_dtx0_log_update(dtx, NULL, NULL);
 * dtx.client.executed:
 *   m0_dtx0_executed(dtx, cas_req->target);
 * dtx.client.done:
 *   m0_dtx0_fini(dtx);
 * dtx.client.cancel:
 *   m0_dtx0_cancel(dtx);
 *   goto dtx.client.done;
 * dtx.client.cb:
 *   TODO: subscribe to dtx0_sm states?
 * dtx.server.init:
 *   dtx = &cas_fom->dtx;
 *   m0_dtx0_init(dtx, reqh->dod);
 *   m0_dtx0_set(dtx, cas_req->txd, serialised(cas_req->cas_op));
 * dtx.server.prepare:
 *   m0_dtx0_credit(dtx, &accum);
 * dtx.server.executed:
 *   m0_dtx0_log_update(dtx, fom->be_tx, cas_fom->is_redo, cas_fom->op);
 * dtx.server.done:
 *   m0_dtx0_fini(dtx);
 */



/* import */
struct m0_dtm0_domain;
struct m0_dtm0_tx_desc;
struct m0_fid;
struct m0_buf;
struct m0_be_tx_credit;
struct m0_be_tx;
struct m0_be_op;

struct m0_dtx0 {
	/** See m0_dtx0_state */
	struct m0_sm dtx0_sm;
};

enum m0_dtx0_state {
	INIT,
	EXECUTED,
	STABLE,
};

M0_INTERNAL int m0_dtx0_init(struct m0_dtx0        *dtx0,
			     struct m0_dtm0_domain *dod);
M0_INTERNAL void m0_dtx0_fini(struct m0_dtx0 *dtx0);

M0_INTERNAL int m0_dtx0_set(struct m0_dtx0                *dtx0,
			    const struct m0_dtm0_tx_desc  *txd,
			    const struct m0_buf           *buf);

M0_INTERNAL void m0_dtx0_timestamp_set(struct m0_dtx0 *dtx0);

M0_INTERNAL int m0_dtx0_participants_set(struct m0_dtx0       *dtx0,
					 const  struct m0_fid *rdtm_svcs,
					 int                   rdtm_svcs_nr);

M0_INTERNAL int m0_dtx0_buf_set(struct m0_dtx0      *dtx0,
				const struct m0_buf *buf);

M0_INTERNAL void m0_dtx0_executed(struct m0_dtx0      *dtx0,
				  const struct m0_fid *rdtm_svc);

M0_INTERNAL void m0_dtx0_credit(struct m0_dtx0         *dtx0,
				struct m0_be_tx_credit *accum);

M0_INTERNAL int m0_dtx0_log_update(struct m0_dtx0 *dtx0,
				   struct m0_be_tx *tx,
				   bool             is_redo,
				   struct m0_be_op *op);

/* XXX */
M0_INTERNAL void m0_dtx0_cancel(struct m0_dtx0 *dtx0);

/** @} end of dtm0 group */
#endif /* __MOTR___DTM0_DTX0_H__ */

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
