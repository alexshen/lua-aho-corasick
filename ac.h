#ifndef AC_H
#define AC_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#  define AC_IMPORT __declspec(dllimport)
#  define AC_EXPORT __declspec(dllexport)
#else
#  if defined(__GNUC__) && __GNUC__ >= 4
#    define AC_IMPORT __attribute__ ((visibility ("default")))
#    define AC_EXPORT __attribute__ ((visibility ("default")))
#  else
#    define AC_IMPORT
#    define AC_EXPORT
#  endif
#endif

#ifdef AC_BUILD_TYPE_SHARED
#  ifdef AC_BUILDING_LIB
#    define AC_API AC_EXPORT
#  else
#    define AC_API AC_IMPORT
#  endif
#else
#  define AC_API
#endif

/* If the subject-string doesn't match any of the given patterns, "match_begin"
 * should be a negative; otherwise the substring of the subject-string,
 * starting from offset "match_begin" to "match_end" incusively,
 * should exactly match the pattern specified by the 'pattern_idx' (i.e.
 * the pattern is "pattern_v[pattern_idx]" where the "pattern_v" is the
 * first actual argument passing to ac_create())
 */
typedef struct {
    int match_begin;
    int match_end;
    int pattern_idx;
} ac_result_t;

struct ac_t;

/* Create an AC instance. "pattern_v" is a vector of patterns, the length of
 * i-th pattern is specified by "pattern_len_v[i]"; the number of patterns
 * is specified by "vect_len".
 *
 * Return the instance on success, or NUL otherwise.
 */
AC_API ac_t* ac_create(const char** pattern_v, unsigned int* pattern_len_v,
                       unsigned int vect_len);

AC_API ac_result_t ac_match(ac_t*, const char *str, unsigned int len);

AC_API ac_result_t ac_match_longest_l(ac_t*, const char *str, unsigned int len);

/* Similar to ac_match() except that it only returns match-begin. The rationale
 * for this interface is that luajit has hard time in dealing with strcture-
 * return-value.
 */
AC_API int ac_match2(ac_t*, const char *str, unsigned int len);

AC_API void ac_free(void*);

#ifdef __cplusplus
}
#endif

#endif /* AC_H */
