/* See LICENSE file for copyright and license details. */

#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))


#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)


void die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);
