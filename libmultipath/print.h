#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED
#include "dm-generic.h"

#define PRINT_PATH_CHECKER   "%i %d %D %p %t %T %o %C"
#define PRINT_MAP_STATUS     "%n %F %Q %N %t %r"
#define PRINT_MAP_STATS      "%n %0 %1 %2 %3 %4"
#define PRINT_MAP_NAMES      "%n %d %w"

struct strbuf;

enum layout_reset {
	LAYOUT_RESET_NOT,
	LAYOUT_RESET_ZERO,
	LAYOUT_RESET_HEADER,
};

/* fieldwidth_t is defined in generic.h */
fieldwidth_t *alloc_path_layout(void);
void _get_path_layout (const struct _vector *gpvec, enum layout_reset,
		       fieldwidth_t *width);
void get_path_layout (vector pathvec, int header, fieldwidth_t *width);
fieldwidth_t *alloc_multipath_layout(void);
void _get_multipath_layout (const struct _vector *gmvec, enum layout_reset,
			    fieldwidth_t *width);
void get_multipath_layout (vector mpvec, int header, fieldwidth_t *width);
int snprint_path_header(struct strbuf *, const char *, const fieldwidth_t *);
int snprint_multipath_header(struct strbuf *, const char *,
			     const fieldwidth_t *);
int _snprint_path (const struct gen_path *, struct strbuf *, const char *,
		   const fieldwidth_t *);
#define snprint_path(buf, fmt, pp, w)		\
	_snprint_path(dm_path_to_gen(pp), buf, fmt, w)
int _snprint_multipath (const struct gen_multipath *, struct strbuf *,
			const char *, const fieldwidth_t *);
#define snprint_multipath(buf, fmt, mp, w)				\
	_snprint_multipath(dm_multipath_to_gen(mp), buf, fmt, w)
int _snprint_multipath_topology (const struct gen_multipath *, struct strbuf *,
				 int verbosity, const fieldwidth_t *);
#define snprint_multipath_topology(buf, mpp, v, w)			\
	_snprint_multipath_topology (dm_multipath_to_gen(mpp), buf, v, w)
int snprint_multipath_topology_json(struct strbuf *, const struct vectors *vecs);
int __snprint_config(const struct config *conf, struct strbuf *buff,
		     const struct _vector *hwtable, const struct _vector *mpvec);
char *snprint_config(const struct config *conf, int *len,
		     const struct _vector *hwtable,
		     const struct _vector *mpvec);
int snprint_multipath_map_json(struct strbuf *, const struct multipath *mpp);
int snprint_blacklist_report(struct config *, struct strbuf *);
int snprint_wildcards(struct strbuf *);
int snprint_status(struct strbuf *, const struct vectors *);
int snprint_devices(struct config *, struct strbuf *, const struct vectors *);
int snprint_path_serial(struct strbuf *, const struct path *);
int snprint_host_wwnn(struct strbuf *, const struct path *);
int snprint_host_wwpn(struct strbuf *, const struct path *);
int snprint_tgt_wwnn(struct strbuf *, const struct path *);
int snprint_tgt_wwpn(struct strbuf *, const struct path *);
#define PROTOCOL_BUF_SIZE sizeof("scsi:unspec")
int snprint_path_protocol(struct strbuf *, const struct path *);

void _print_multipath_topology (const struct gen_multipath * gmp,
				int verbosity);
#define print_multipath_topology(mpp, v) \
	_print_multipath_topology(dm_multipath_to_gen(mpp), v)

void print_all_paths (vector pathvec, int banner);

int snprint_path_attr(const struct gen_path* gp,
		      struct strbuf *buf, char wildcard);
int snprint_pathgroup_attr(const struct gen_pathgroup* gpg,
			   struct strbuf *buf, char wildcard);
int snprint_multipath_attr(const struct gen_multipath* gm,
			   struct strbuf *buf, char wildcard);
int snprint_multipath_style(const struct gen_multipath *gmp,
			    struct strbuf *style, int verbosity);
#endif /* PRINT_H_INCLUDED */
