TEST({ 0x00000000,     { 3,  {0xba, 0xa7, 0x0e},                  }, "mov    dx,0xea7" })
TEST({ 0x00000008,     { 2,  {0xb4, 0x30},                        }, "mov    ah,0x30" })
TEST({ 0x0000000a,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x0000000c,     { 4,  {0x8b, 0x2e, 0x02, 0x00},            }, "mov    bp,WORD PTR ds:0x2" })
TEST({ 0x00000010,     { 4,  {0x8b, 0x1e, 0x2c, 0x00},            }, "mov    bx,WORD PTR ds:0x2c" })
TEST({ 0x00000016,     { 3,  {0xa3, 0x7d, 0x00},                  }, "mov    WORD PTR ds:0x7d,ax" })
TEST({ 0x00000019,     { 4,  {0x8c, 0x06, 0x7b, 0x00},            }, "mov    WORD PTR ds:0x7b,es" })
TEST({ 0x0000001d,     { 4,  {0x89, 0x1e, 0x77, 0x00},            }, "mov    WORD PTR ds:0x77,bx" })
TEST({ 0x00000021,     { 4,  {0x89, 0x2e, 0x91, 0x00},            }, "mov    WORD PTR ds:0x91,bp" })
TEST({ 0x00000025,     { 3,  {0xe8, 0x52, 0x01},                  }, "call   0x17a" })
TEST({ 0x00000028,     { 4,  {0xc4, 0x3e, 0x75, 0x00},            }, "les    di,DWORD PTR ds:0x75" })
TEST({ 0x0000002c,     { 2,  {0x8b, 0xc7},                        }, "mov    ax,di" })
TEST({ 0x0000002e,     { 2,  {0x8b, 0xd8},                        }, "mov    bx,ax" })
TEST({ 0x00000030,     { 3,  {0xb9, 0xff, 0x7f},                  }, "mov    cx,0x7fff" })
TEST({ 0x00000033,     { 1,  {0xfc},                              }, "cld" })
TEST({ 0x00000003,     { 5,  {0x2e, 0x89, 0x16, 0x60, 0x02},      }, "mov    WORD PTR cs:0x260,dx" })
TEST({ 0x00000014,     { 2,  {0x8e, 0xda},                        }, "mov    ds,dx" })
TEST({ 0x00000036,     { 2,  {0xe3, 0x43},                        }, "jcxz   0x7b" })
TEST({ 0x00000038,     { 1,  {0x43},                              }, "inc    bx" })
TEST({ 0x00000039,     { 3,  {0x26, 0x38, 0x05},                  }, "cmp    BYTE PTR es:[di],al" })
TEST({ 0x0000003c,     { 2,  {0x75, 0xf6},                        }, "jne    0x34" })
TEST({ 0x0000003e,     { 3,  {0x80, 0xcd, 0x80},                  }, "or     ch,0x80" })
TEST({ 0x00000041,     { 2,  {0xf7, 0xd9},                        }, "neg    cx" })
TEST({ 0x00000043,     { 4,  {0x89, 0x0e, 0x75, 0x00},            }, "mov    WORD PTR ds:0x75,cx" })
TEST({ 0x00000047,     { 3,  {0xb9, 0x02, 0x00},                  }, "mov    cx,0x2" })
TEST({ 0x0000004a,     { 2,  {0xd3, 0xe3},                        }, "shl    bx,cl" })
TEST({ 0x0000004c,     { 3,  {0x83, 0xc3, 0x10},                  }, "add    bx,0x10" })
TEST({ 0x0000004f,     { 3,  {0x83, 0xe3, 0xf0},                  }, "and    bx,0xfff0" })
TEST({ 0x00000052,     { 4,  {0x89, 0x1e, 0x79, 0x00},            }, "mov    WORD PTR ds:0x79,bx" })
TEST({ 0x00000056,     { 2,  {0x8c, 0xd2},                        }, "mov    dx,ss" })
TEST({ 0x00000058,     { 2,  {0x2b, 0xea},                        }, "sub    bp,dx" })
TEST({ 0x0000005a,     { 3,  {0xbf, 0xa7, 0x0e},                  }, "mov    di,0xea7" })
TEST({ 0x0000005d,     { 2,  {0x8e, 0xc7},                        }, "mov    es,di" })
TEST({ 0x0000005f,     { 5,  {0x26, 0x8b, 0x3e, 0x2e, 0x44},      }, "mov    di,WORD PTR es:0x442e" })
TEST({ 0x00000064,     { 4,  {0x81, 0xff, 0x00, 0x02},            }, "cmp    di,0x200" })
TEST({ 0x00000068,     { 2,  {0x73, 0x08},                        }, "jae    0x72" })
TEST({ 0x0000006a,     { 3,  {0xbf, 0x00, 0x02},                  }, "mov    di,0x200" })
TEST({ 0x0000006d,     { 5,  {0x26, 0x89, 0x3e, 0x2e, 0x44},      }, "mov    WORD PTR es:0x442e,di" })
TEST({ 0x00000072,     { 2,  {0xb1, 0x04},                        }, "mov    cl,0x4" })
TEST({ 0x00000074,     { 2,  {0xd3, 0xef},                        }, "shr    di,cl" })
TEST({ 0x00000076,     { 1,  {0x47},                              }, "inc    di" })
TEST({ 0x00000077,     { 2,  {0x3b, 0xef},                        }, "cmp    bp,di" })
TEST({ 0x00000079,     { 2,  {0x73, 0x03},                        }, "jae    0x7e" })
TEST({ 0x0000007b,     { 3,  {0xe9, 0xcb, 0x01},                  }, "jmp    0x249" })
TEST({ 0x0000007e,     { 2,  {0x8b, 0xdf},                        }, "mov    bx,di" })
TEST({ 0x00000080,     { 2,  {0x03, 0xda},                        }, "add    bx,dx" })
TEST({ 0x00000082,     { 4,  {0x89, 0x1e, 0x89, 0x00},            }, "mov    WORD PTR ds:0x89,bx" })
TEST({ 0x00000086,     { 4,  {0x89, 0x1e, 0x8d, 0x00},            }, "mov    WORD PTR ds:0x8d,bx" })
TEST({ 0x0000008a,     { 3,  {0xa1, 0x7b, 0x00},                  }, "mov    ax,WORD PTR ds:0x7b" })
TEST({ 0x0000008d,     { 2,  {0x2b, 0xd8},                        }, "sub    bx,ax" })
TEST({ 0x0000008f,     { 2,  {0x8e, 0xc0},                        }, "mov    es,ax" })
TEST({ 0x00000091,     { 2,  {0xb4, 0x4a},                        }, "mov    ah,0x4a" })
TEST({ 0x00000093,     { 1,  {0x57},                              }, "push   di" })
TEST({ 0x00000094,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x00000096,     { 1,  {0x5f},                              }, "pop    di" })
TEST({ 0x00000097,     { 2,  {0xd3, 0xe7},                        }, "shl    di,cl" })
TEST({ 0x00000099,     { 1,  {0xfa},                              }, "cli" })
TEST({ 0x0000009a,     { 2,  {0x8e, 0xd2},                        }, "mov    ss,dx" })
TEST({ 0x0000009c,     { 2,  {0x8b, 0xe7},                        }, "mov    sp,di" })
TEST({ 0x0000009e,     { 1,  {0xfb},                              }, "sti" })
TEST({ 0x0000009f,     { 3,  {0xb8, 0xa7, 0x0e},                  }, "mov    ax,0xea7" })
TEST({ 0x000000a2,     { 2,  {0x8e, 0xc0},                        }, "mov    es,ax" })
TEST({ 0x000000a4,     { 5,  {0x26, 0x89, 0x3e, 0x2e, 0x44},      }, "mov    WORD PTR es:0x442e,di" })
TEST({ 0x000000a9,     { 2,  {0x33, 0xc0},                        }, "xor    ax,ax" })
TEST({ 0x000000ab,     { 5,  {0x2e, 0x8e, 0x06, 0x60, 0x02},      }, "mov    es,WORD PTR cs:0x260" })
TEST({ 0x000000b0,     { 3,  {0xbf, 0x52, 0x45},                  }, "mov    di,0x4552" })
TEST({ 0x000000b3,     { 3,  {0xb9, 0x04, 0xbd},                  }, "mov    cx,0xbd04" })
TEST({ 0x000000b6,     { 2,  {0x2b, 0xcf},                        }, "sub    cx,di" })
TEST({ 0x000000b8,     { 1,  {0xfc},                              }, "cld" })
TEST({ 0x000000bb,     { 5,  {0x83, 0x3e, 0xa0, 0x43, 0x14},      }, "cmp    WORD PTR ds:0x43a0,0x14" })
TEST({ 0x000000c0,     { 2,  {0x76, 0x47},                        }, "jbe    0x109" })
TEST({ 0x000000c2,     { 5,  {0x80, 0x3e, 0x7d, 0x00, 0x03},      }, "cmp    BYTE PTR ds:0x7d,0x3" })
TEST({ 0x000000c7,     { 2,  {0x72, 0x40},                        }, "jb     0x109" })
TEST({ 0x000000c9,     { 2,  {0x77, 0x07},                        }, "ja     0xd2" })
TEST({ 0x000000cb,     { 5,  {0x80, 0x3e, 0x7e, 0x00, 0x1e},      }, "cmp    BYTE PTR ds:0x7e,0x1e" })
TEST({ 0x000000d0,     { 2,  {0x72, 0x37},                        }, "jb     0x109" })
TEST({ 0x000000d2,     { 3,  {0xb8, 0x01, 0x58},                  }, "mov    ax,0x5801" })
TEST({ 0x000000d5,     { 3,  {0xbb, 0x02, 0x00},                  }, "mov    bx,0x2" })
TEST({ 0x000000d8,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000000da,     { 2,  {0x72, 0x2a},                        }, "jb     0x106" })
TEST({ 0x000000dc,     { 2,  {0xb4, 0x67},                        }, "mov    ah,0x67" })
TEST({ 0x000000de,     { 4,  {0x8b, 0x1e, 0xa0, 0x43},            }, "mov    bx,WORD PTR ds:0x43a0" })
TEST({ 0x000000e2,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000000e4,     { 2,  {0x72, 0x20},                        }, "jb     0x106" })
TEST({ 0x000000e6,     { 2,  {0xb4, 0x48},                        }, "mov    ah,0x48" })
TEST({ 0x000000e8,     { 3,  {0xbb, 0x01, 0x00},                  }, "mov    bx,0x1" })
TEST({ 0x000000eb,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000000ed,     { 2,  {0x72, 0x17},                        }, "jb     0x106" })
TEST({ 0x000000ef,     { 1,  {0x40},                              }, "inc    ax" })
TEST({ 0x000000f0,     { 3,  {0xa3, 0x91, 0x00},                  }, "mov    WORD PTR ds:0x91,ax" })
TEST({ 0x000000f3,     { 1,  {0x48},                              }, "dec    ax" })
TEST({ 0x000000f4,     { 2,  {0x8e, 0xc0},                        }, "mov    es,ax" })
TEST({ 0x000000f6,     { 2,  {0xb4, 0x49},                        }, "mov    ah,0x49" })
TEST({ 0x000000f8,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000000fa,     { 2,  {0x72, 0x0a},                        }, "jb     0x106" })
TEST({ 0x000000fc,     { 3,  {0xb8, 0x01, 0x58},                  }, "mov    ax,0x5801" })
TEST({ 0x000000ff,     { 3,  {0xbb, 0x00, 0x00},                  }, "mov    bx,0x0" })
TEST({ 0x00000102,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x00000104,     { 2,  {0x73, 0x03},                        }, "jae    0x109" })
TEST({ 0x00000106,     { 3,  {0xe9, 0x40, 0x01},                  }, "jmp    0x249" })
TEST({ 0x00000109,     { 2,  {0xb4, 0x00},                        }, "mov    ah,0x0" })
TEST({ 0x0000010b,     { 2,  {0xcd, 0x1a},                        }, "int    0x1a" })
TEST({ 0x0000010d,     { 4,  {0x89, 0x16, 0x81, 0x00},            }, "mov    WORD PTR ds:0x81,dx" })
TEST({ 0x00000111,     { 4,  {0x89, 0x0e, 0x83, 0x00},            }, "mov    WORD PTR ds:0x83,cx" })
TEST({ 0x00000115,     { 2,  {0x0a, 0xc0},                        }, "or     al,al" })
TEST({ 0x00000117,     { 2,  {0x74, 0x0c},                        }, "je     0x125" })
TEST({ 0x00000119,     { 3,  {0xb8, 0x40, 0x00},                  }, "mov    ax,0x40" })
TEST({ 0x0000011c,     { 2,  {0x8e, 0xc0},                        }, "mov    es,ax" })
TEST({ 0x0000011e,     { 3,  {0xbb, 0x70, 0x00},                  }, "mov    bx,0x70" })
TEST({ 0x00000121,     { 4,  {0x26, 0xc6, 0x07, 0x01},            }, "mov    BYTE PTR es:[bx],0x1" })
TEST({ 0x00000125,     { 2,  {0x33, 0xed},                        }, "xor    bp,bp" })
TEST({ 0x00000127,     { 5,  {0x2e, 0x8e, 0x06, 0x60, 0x02},      }, "mov    es,WORD PTR cs:0x260" })
TEST({ 0x0000012c,     { 3,  {0xbe, 0x2e, 0x45},                  }, "mov    si,0x452e" })
TEST({ 0x0000012f,     { 3,  {0xbf, 0x4c, 0x45},                  }, "mov    di,0x454c" })
TEST({ 0x00000132,     { 3,  {0xe8, 0xb5, 0x00},                  }, "call   0x1ea" })
TEST({ 0x00000135,     { 4,  {0xff, 0x36, 0x73, 0x00},            }, "push   WORD PTR ds:0x73" })
TEST({ 0x00000139,     { 4,  {0xff, 0x36, 0x71, 0x00},            }, "push   WORD PTR ds:0x71" })
TEST({ 0x0000013d,     { 4,  {0xff, 0x36, 0x6f, 0x00},            }, "push   WORD PTR ds:0x6f" })
TEST({ 0x00000141,     { 4,  {0xff, 0x36, 0x6d, 0x00},            }, "push   WORD PTR ds:0x6d" })
TEST({ 0x00000145,     { 4,  {0xff, 0x36, 0x6b, 0x00},            }, "push   WORD PTR ds:0x6b" })
TEST({ 0x00000149,     { 5,  {0x9a, 0x38, 0x0b, 0xe0, 0x02},      }, "callf  0x2e0:0xb38" })
TEST({ 0x0000014e,     { 1,  {0x50},                              }, "push   ax" })
TEST({ 0x0000014f,     { 1,  {0x90},                              }, "nop" })
TEST({ 0x00000150,     { 1,  {0x0e},                              }, "push   cs" })
TEST({ 0x00000151,     { 3,  {0xe8, 0xca, 0x01},                  }, "call   0x31e" })
TEST({ 0x00000154,     { 5,  {0x2e, 0x8e, 0x06, 0x60, 0x02},      }, "mov    es,WORD PTR cs:0x260" })
TEST({ 0x00000159,     { 1,  {0x56},                              }, "push   si" })
TEST({ 0x0000015a,     { 1,  {0x57},                              }, "push   di" })
TEST({ 0x0000015b,     { 3,  {0xbe, 0x4c, 0x45},                  }, "mov    si,0x454c" })
TEST({ 0x0000015e,     { 3,  {0xbf, 0x52, 0x45},                  }, "mov    di,0x4552" })
TEST({ 0x00000161,     { 3,  {0xe8, 0x86, 0x00},                  }, "call   0x1ea" })
TEST({ 0x00000164,     { 1,  {0x5f},                              }, "pop    di" })
TEST({ 0x00000165,     { 1,  {0x5e},                              }, "pop    si" })
TEST({ 0x00000166,     { 1,  {0xcb},                              }, "retf" })
TEST({ 0x00000167,     { 1,  {0xcb},                              }, "retf" })
TEST({ 0x00000168,     { 2,  {0x8b, 0xec},                        }, "mov    bp,sp" })
TEST({ 0x0000016a,     { 2,  {0xb4, 0x4c},                        }, "mov    ah,0x4c" })
TEST({ 0x0000016c,     { 3,  {0x8a, 0x46, 0x04},                  }, "mov    al,BYTE PTR [bp+0x4]" })
TEST({ 0x0000016f,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x00000171,     { 3,  {0xb9, 0x0e, 0x00},                  }, "mov    cx,0xe" })
TEST({ 0x00000174,     { 3,  {0xba, 0x2f, 0x00},                  }, "mov    dx,0x2f" })
TEST({ 0x00000177,     { 3,  {0xe9, 0xd5, 0x00},                  }, "jmp    0x24f" })
TEST({ 0x0000017a,     { 1,  {0x1e},                              }, "push   ds" })
TEST({ 0x0000017b,     { 3,  {0xb8, 0x00, 0x35},                  }, "mov    ax,0x3500" })
TEST({ 0x0000017e,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x00000180,     { 4,  {0x89, 0x1e, 0x5b, 0x00},            }, "mov    WORD PTR ds:0x5b,bx" })
TEST({ 0x00000184,     { 4,  {0x8c, 0x06, 0x5d, 0x00},            }, "mov    WORD PTR ds:0x5d,es" })
TEST({ 0x00000188,     { 3,  {0xb8, 0x04, 0x35},                  }, "mov    ax,0x3504" })
TEST({ 0x0000018b,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x0000018d,     { 4,  {0x89, 0x1e, 0x5f, 0x00},            }, "mov    WORD PTR ds:0x5f,bx" })
TEST({ 0x00000191,     { 4,  {0x8c, 0x06, 0x61, 0x00},            }, "mov    WORD PTR ds:0x61,es" })
TEST({ 0x00000195,     { 3,  {0xb8, 0x05, 0x35},                  }, "mov    ax,0x3505" })
TEST({ 0x00000198,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x0000019a,     { 4,  {0x89, 0x1e, 0x63, 0x00},            }, "mov    WORD PTR ds:0x63,bx" })
TEST({ 0x0000019e,     { 4,  {0x8c, 0x06, 0x65, 0x00},            }, "mov    WORD PTR ds:0x65,es" })
TEST({ 0x000001a2,     { 3,  {0xb8, 0x06, 0x35},                  }, "mov    ax,0x3506" })
TEST({ 0x000001a5,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000001a7,     { 4,  {0x89, 0x1e, 0x67, 0x00},            }, "mov    WORD PTR ds:0x67,bx" })
TEST({ 0x000001ab,     { 4,  {0x8c, 0x06, 0x69, 0x00},            }, "mov    WORD PTR ds:0x69,es" })
TEST({ 0x000001af,     { 3,  {0xb8, 0x00, 0x25},                  }, "mov    ax,0x2500" })
TEST({ 0x000001b2,     { 2,  {0x8c, 0xca},                        }, "mov    dx,cs" })
TEST({ 0x000001b4,     { 2,  {0x8e, 0xda},                        }, "mov    ds,dx" })
TEST({ 0x000001b6,     { 3,  {0xba, 0x71, 0x01},                  }, "mov    dx,0x171" })
TEST({ 0x000001b9,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000001bb,     { 1,  {0x1f},                              }, "pop    ds" })
TEST({ 0x000001bc,     { 1,  {0xc3},                              }, "ret" })
TEST({ 0x000001bd,     { 1,  {0x1e},                              }, "push   ds" })
TEST({ 0x000001be,     { 3,  {0xb8, 0x00, 0x25},                  }, "mov    ax,0x2500" })
TEST({ 0x000001c1,     { 4,  {0xc5, 0x16, 0x5b, 0x00},            }, "lds    dx,DWORD PTR ds:0x5b" })
TEST({ 0x000001c5,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000001c7,     { 1,  {0x1f},                              }, "pop    ds" })
TEST({ 0x000001c8,     { 1,  {0x1e},                              }, "push   ds" })
TEST({ 0x000001c9,     { 3,  {0xb8, 0x04, 0x25},                  }, "mov    ax,0x2504" })
TEST({ 0x000001cc,     { 4,  {0xc5, 0x16, 0x5f, 0x00},            }, "lds    dx,DWORD PTR ds:0x5f" })
TEST({ 0x000001d0,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000001d2,     { 1,  {0x1f},                              }, "pop    ds" })
TEST({ 0x000001d3,     { 1,  {0x1e},                              }, "push   ds" })
TEST({ 0x000001d4,     { 3,  {0xb8, 0x05, 0x25},                  }, "mov    ax,0x2505" })
TEST({ 0x000001d7,     { 4,  {0xc5, 0x16, 0x63, 0x00},            }, "lds    dx,DWORD PTR ds:0x63" })
TEST({ 0x000001db,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000001dd,     { 1,  {0x1f},                              }, "pop    ds" })
TEST({ 0x000001de,     { 1,  {0x1e},                              }, "push   ds" })
TEST({ 0x000001df,     { 3,  {0xb8, 0x06, 0x25},                  }, "mov    ax,0x2506" })
TEST({ 0x000001e2,     { 4,  {0xc5, 0x16, 0x67, 0x00},            }, "lds    dx,DWORD PTR ds:0x67" })
TEST({ 0x000001e6,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x000001e8,     { 1,  {0x1f},                              }, "pop    ds" })
TEST({ 0x000001e9,     { 1,  {0xcb},                              }, "retf" })
TEST({ 0x000001ea,     { 4,  {0x81, 0xfe, 0x2e, 0x45},            }, "cmp    si,0x452e" })
TEST({ 0x000001ee,     { 2,  {0x74, 0x04},                        }, "je     0x1f4" })
TEST({ 0x000001f0,     { 2,  {0x32, 0xe4},                        }, "xor    ah,ah" })
TEST({ 0x000001f2,     { 2,  {0xeb, 0x02},                        }, "jmp    0x1f6" })
TEST({ 0x000001f4,     { 2,  {0xb4, 0xff},                        }, "mov    ah,0xff" })
TEST({ 0x000001f6,     { 2,  {0x8b, 0xd7},                        }, "mov    dx,di" })
TEST({ 0x000001f8,     { 2,  {0x8b, 0xde},                        }, "mov    bx,si" })
TEST({ 0x000001fa,     { 2,  {0x3b, 0xdf},                        }, "cmp    bx,di" })
TEST({ 0x000001fc,     { 2,  {0x74, 0x23},                        }, "je     0x221" })
TEST({ 0x000001fe,     { 4,  {0x26, 0x80, 0x3f, 0xff},            }, "cmp    BYTE PTR es:[bx],0xff" })
TEST({ 0x00000202,     { 2,  {0x74, 0x18},                        }, "je     0x21c" })
TEST({ 0x00000204,     { 4,  {0x81, 0xfe, 0x2e, 0x45},            }, "cmp    si,0x452e" })
TEST({ 0x00000208,     { 2,  {0x74, 0x06},                        }, "je     0x210" })
TEST({ 0x0000020a,     { 4,  {0x26, 0x3a, 0x67, 0x01},            }, "cmp    ah,BYTE PTR es:[bx+0x1]" })
TEST({ 0x0000020e,     { 2,  {0xeb, 0x04},                        }, "jmp    0x214" })
TEST({ 0x00000210,     { 4,  {0x26, 0x38, 0x67, 0x01},            }, "cmp    BYTE PTR es:[bx+0x1],ah" })
TEST({ 0x00000214,     { 2,  {0x77, 0x06},                        }, "ja     0x21c" })
TEST({ 0x00000216,     { 4,  {0x26, 0x8a, 0x67, 0x01},            }, "mov    ah,BYTE PTR es:[bx+0x1]" })
TEST({ 0x0000021a,     { 2,  {0x8b, 0xd3},                        }, "mov    dx,bx" })
TEST({ 0x0000021c,     { 3,  {0x83, 0xc3, 0x06},                  }, "add    bx,0x6" })
TEST({ 0x0000021f,     { 2,  {0xeb, 0xd9},                        }, "jmp    0x1fa" })
TEST({ 0x00000221,     { 2,  {0x3b, 0xd7},                        }, "cmp    dx,di" })
TEST({ 0x00000223,     { 2,  {0x74, 0x1b},                        }, "je     0x240" })
TEST({ 0x00000225,     { 2,  {0x8b, 0xda},                        }, "mov    bx,dx" })
TEST({ 0x00000227,     { 4,  {0x26, 0x80, 0x3f, 0x00},            }, "cmp    BYTE PTR es:[bx],0x0" })
TEST({ 0x0000022b,     { 4,  {0x26, 0xc6, 0x07, 0xff},            }, "mov    BYTE PTR es:[bx],0xff" })
TEST({ 0x0000022f,     { 1,  {0x06},                              }, "push   es" })
TEST({ 0x00000230,     { 2,  {0x74, 0x07},                        }, "je     0x239" })
TEST({ 0x00000232,     { 4,  {0x26, 0xff, 0x5f, 0x02},            }, "callf  DWORD PTR es:[bx+0x2]" })
TEST({ 0x00000236,     { 1,  {0x07},                              }, "pop    es" })
TEST({ 0x00000237,     { 2,  {0xeb, 0xb1},                        }, "jmp    0x1ea" })
TEST({ 0x00000239,     { 4,  {0x26, 0xff, 0x57, 0x02},            }, "call   WORD PTR es:[bx+0x2]" })
TEST({ 0x0000023d,     { 1,  {0x07},                              }, "pop    es" })
TEST({ 0x0000023e,     { 2,  {0xeb, 0xaa},                        }, "jmp    0x1ea" })
TEST({ 0x00000240,     { 1,  {0xc3},                              }, "ret" })
TEST({ 0x00000241,     { 2,  {0xb4, 0x40},                        }, "mov    ah,0x40" })
TEST({ 0x00000243,     { 3,  {0xbb, 0x02, 0x00},                  }, "mov    bx,0x2" })
TEST({ 0x00000246,     { 2,  {0xcd, 0x21},                        }, "int    0x21" })
TEST({ 0x00000248,     { 1,  {0xc3},                              }, "ret" })
TEST({ 0x00000249,     { 3,  {0xb9, 0x1e, 0x00},                  }, "mov    cx,0x1e" })
TEST({ 0x0000024c,     { 3,  {0xba, 0x3d, 0x00},                  }, "mov    dx,0x3d" })
TEST({ 0x0000024f,     { 5,  {0x2e, 0x8e, 0x1e, 0x60, 0x02},      }, "mov    ds,WORD PTR cs:0x260" })
TEST({ 0x00000254,     { 3,  {0xe8, 0xea, 0xff},                  }, "call   0x241" })
TEST({ 0x00000257,     { 3,  {0xb8, 0x03, 0x00},                  }, "mov    ax,0x3" })
TEST({ 0x0000025a,     { 1,  {0x50},                              }, "push   ax" })
TEST({ 0x0000025b,     { 1,  {0x90},                              }, "nop" })
TEST({ 0x0000025c,     { 1,  {0x0e},                              }, "push   cs" })
TEST({ 0x0000025d,     { 3,  {0xe8, 0xcd, 0x00},                  }, "call   0x32d" })
TEST({ 0x00000034,     { 2,  {0xf2, 0xae},                        }, "repnz scas al,BYTE PTR es:[di]" })
TEST({ 0x000000b9,     { 2,  {0xf3, 0xaa},                        }, "rep stos BYTE PTR es:[di],al" })
