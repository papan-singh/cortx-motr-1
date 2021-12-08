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

/**
 * @addtogroup dtm0
 *
 * @{
 */

#define M0_TRACE_SUBSYSTEM M0_TRACE_SUBSYS_DTM0
#include "lib/trace.h"

#include "dtm0/domain.h"

#include "lib/bob.h"            /* M0_BOB_DEFINE */
#include "module/instance.h"    /* m0_get */


static const struct m0_bob_type dtm0_domain_bob_type = {
	.bt_name         = "m0_dtm0_domain",
	.bt_magix_offset = M0_MAGIX_OFFSET(struct m0_dtm0_domain, dod_magix),
	.bt_magix        = M0_DTM0_DOMAIN_MAGIC,
};
M0_BOB_DEFINE(static, &dtm0_domain_bob_type, m0_dtm0_domain);

static struct m0_dtm0_domain *dtm0_module2domain(struct m0_module *module)
{
	return bob_of(module, struct m0_dtm0_domain, dod_module,
	              &dtm0_domain_bob_type);
}

static int dtm0_domain_level_enter(struct m0_module *module);
static void dtm0_domain_level_leave(struct m0_module *module);

#define DTM0_DOMAIN_LEVEL(level) [level] = {            \
		.ml_name  = #level,                     \
		.ml_enter = &dtm0_domain_level_enter,    \
		.ml_leave = &dtm0_domain_level_leave,    \
	}

enum dtm0_domain_level {
	M0_DTM0_DOMAIN_LEVEL_INIT,
	M0_DTM0_DOMAIN_LEVEL_READY,
};

static const struct m0_modlev levels_dtm0_domain[] = {
	DTM0_DOMAIN_LEVEL(M0_DTM0_DOMAIN_LEVEL_INIT),
	DTM0_DOMAIN_LEVEL(M0_DTM0_DOMAIN_LEVEL_READY),
};
#undef DTM0_DOMAIN_LEVEL

static int dtm0_domain_level_enter(struct m0_module *module)
{
	enum dtm0_domain_level  level = module->m_cur + 1;
	struct m0_dtm0_domain  *dod = dtm0_module2domain(module);

	M0_ENTRY("dod=%p level=%d level_name=%s",
	         dod, level, levels_dtm0_domain[level].ml_name);
	switch (level) {
	case M0_DTM0_DOMAIN_LEVEL_INIT:
		return M0_RC(0);
	case M0_DTM0_DOMAIN_LEVEL_READY:
		return M0_RC(0);
	default:
		M0_IMPOSSIBLE("Unexpected level: %d", level);
	}
}

static void dtm0_domain_level_leave(struct m0_module *module)
{
	enum dtm0_domain_level  level = module->m_cur;
	struct m0_dtm0_domain  *dod = dtm0_module2domain(module);

	M0_ENTRY("dod=%p level=%d level_name=%s",
	         dod, level, levels_dtm0_domain[level].ml_name);
	switch (level) {
	case M0_DTM0_DOMAIN_LEVEL_INIT:
		break;
	case M0_DTM0_DOMAIN_LEVEL_READY:
		break;
	default:
		M0_IMPOSSIBLE("Unexpected level: %d", level);
	}
}

M0_INTERNAL int m0_dtm0_domain_init(struct m0_dtm0_domain     *dod,
				    struct m0_dtm0_domain_cfg *dod_cfg)
{
	int rc;

	M0_ENTRY("dod=%p dod_cfg=%p", dod, dod_cfg);
	m0_module_setup(&dod->dod_module, "m0_dtm0_domain module",
	                levels_dtm0_domain, ARRAY_SIZE(levels_dtm0_domain),
	                m0_get());
	dod->dod_cfg = *dod_cfg;        /* XXX */
	m0_dtm0_domain_bob_init(dod);
	rc = m0_module_init(&dod->dod_module, M0_DTM0_DOMAIN_LEVEL_READY);
	if (rc != 0)
		m0_module_fini(&dod->dod_module, M0_MODLEV_NONE);
	return M0_RC(rc);
}

M0_INTERNAL void m0_dtm0_domain_fini(struct m0_dtm0_domain *dod)
{
	m0_module_fini(&dod->dod_module, M0_MODLEV_NONE);
	m0_dtm0_domain_bob_fini(dod);
}

M0_INTERNAL int m0_dtm0_domain_create(struct m0_dtm0_domain            *dod,
				      struct m0_dtm0_domain_create_cfg *dc_cfg)
{
	return 0;
}

M0_INTERNAL void m0_dtm0_domain_destroy(struct m0_dtm0_domain *dod)
{
}

#undef M0_TRACE_SUBSYSTEM

/** @} end of dtm0 group */

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
