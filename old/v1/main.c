#include "dis86.h"
#include "dis86_private.h"

static dis86_t *dis_exit = NULL;
static void on_fail()
{
  if (!dis_exit) return;
  bin_dump(dis_exit->b);
}

typedef struct segoff segoff_t;
struct segoff
{
  u16 seg;
  u16 off;
};

static u16 parse_hex_u16(const char *s, size_t len)
{
  if (len > 4) FAIL("Hex string too long to fit in u16");

  u16 ret = 0;
  for (size_t i = 0; i < len; i++) {
    char c = s[i];
    if ('0' <= c && c <= '9') {
      ret = ret*16 + (c-'0');
    } else if ('a' <= c && c <= 'f') {
      ret = ret*16 + (c-'a'+10);
    } else if ('A' <= c && c <= 'F') {
      ret = ret*16 + (c-'A'+10);
    } else {
      FAIL("Invalid hex string: '%.*s'", (int)len, s);
    }
  }

  return ret;
}

static segoff_t parse_segoff(const char *s)
{
  const char *end = s + strlen(s);

  const char *colon = strchr(s, ':');
  if (!colon) FAIL("Invalid segoff: '%s'", s);

  segoff_t ret;
  ret.seg = parse_hex_u16(s, colon-s);
  ret.off = parse_hex_u16(colon+1, end-(colon+1));
  return ret;
}

static size_t segoff_abs(segoff_t s)
{
  return (size_t)s.seg * 16 + (size_t)s.off;
}

int main(int argc, char *argv[])
{
  atexit(on_fail);

  if (argc != 4) {
    fprintf(stderr, "usage: %s <binary> <start-seg-off> <end-seg-off>\n", argv[0]);
    return 1;
  }
  const char *filename = argv[1];
  segoff_t start = parse_segoff(argv[2]);
  segoff_t end = parse_segoff(argv[3]);

  size_t start_idx = segoff_abs(start);
  size_t end_idx = segoff_abs(end);

  size_t mem_sz = 0;
  char *mem = read_file(filename, &mem_sz);

  /* printf("start_idx: %zu\n", start_idx); */
  /* printf("end_idx: %zu\n", end_idx); */
  /* hexdump((u8*)mem+start_idx, end_idx-start_idx); */
  /* exit(42); */

  char *region = &mem[start_idx];
  size_t region_sz = end_idx - start_idx;

  dis86_t *d = dis86_new(start_idx, region, region_sz);
  if (!d) FAIL("Failed to allocate dis86 instance");
  free(mem);
  dis_exit = d;

  char *s;
  while (1) {
    size_t addr, n_bytes;
    dis86_instr_t *ins = dis86_next(d, &addr, &n_bytes);
    if (!ins) break;

    s = dis86_print_c_code(d, ins, addr, n_bytes);
    printf("%-30s // ", s);
    free(s);

    s = dis86_print_intel_syntax(d, ins, addr, n_bytes, false);
    printf("%s\n", s);
    free(s);
  }

  dis_exit = NULL;
  dis86_delete(d);
  return 0;
}
