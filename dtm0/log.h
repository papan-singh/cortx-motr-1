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

#ifndef __MOTR___DTM0_LOG_H__
#define __MOTR___DTM0_LOG_H__

/**
 * @defgroup dtm0
 *
 * @{
 */

struct m0_dtm0_log_cfg {
};

struct m0_dtm0_log_create_cfg {
};

struct m0_dtm0_log {
};


M0_INTERNAL int m0_dtm0_log_init(struct m0_dtm0_log     *dol,
				 struct m0_dtm0_log_cfg *dol_cfg);

M0_INTERNAL void m0_dtm0_log_fini(struct m0_dtm0_log *dol);

M0_INTERNAL int m0_dtm0_log__create(struct m0_dtm0_log            *dol,
				    struct m0_dtm0_log_create_cfg *dlc_cfg);

M0_INTERNAL void m0_dtm0_log_destroy(struct m0_dtm0_log *dol);

/** @} end of dtm0 group */
#endif /* __MOTR___DTM0_LOG_H__ */

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
