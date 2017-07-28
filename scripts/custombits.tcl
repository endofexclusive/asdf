# fieldname, bitnum, mask
list \
      [list int \
              [list setclr] \
              [list inten] \
              [list all 0 0x3fff] \
              [list exter 13] \
              [list dsksync] \
              [list rbf] \
              [list aud3] \
              [list aud2] \
              [list aud1] \
              [list aud0] \
              [list blit] \
              [list vertb] \
              [list coper] \
              [list ports] \
              [list softint] \
              [list dskblk] \
              [list tbe] \
      ] \
      [list dma \
              [list setclr] \
              [list bltdone] \
              [list bltnzero] \
              [list blithog 10] \
              [list master] \
              [list all 0 0x1ff] \
              [list raster 8] \
              [list copper] \
              [list blitter] \
              [list sprite] \
              [list disk] \
              [list audio 0 0xf] \
              [list aud3 3] \
              [list aud2] \
              [list aud1] \
              [list aud0] \
      ] \
      [list vpos \
              [list lof] \
              [list v8 0] \
      ] \
      [list vhpos \
              [list v 8 0xff] \
              [list h 0 0xff] \
      ] \
      [list bplcon0 \
              [list hires] \
              [list bpu 12 0x7] \
              [list bpu2 14] \
              [list bpu1] \
              [list bpu0] \
              [list homod] \
              [list dblpf] \
              [list color] \
              [list gaud] \
              [list lpen 3] \
              [list lace] \
              [list ersy] \
      ] \
      [list bplcon1 \
              [list pf2h3 7] \
              [list pf2h2] \
              [list pf2h1] \
              [list pf2h0] \
              [list pf2h 4 0xf] \
              [list pf1h3 3] \
              [list pf1h2] \
              [list pf1h1] \
              [list pf1h0] \
              [list pf1h 0 0xf] \
      ] \
      [list serdat \
              [list ovrun] \
              [list rbf] \
              [list tbe] \
              [list trse] \
              [list rxd] \
              [list stp9 9] \
              [list stp8 8] \
              [list db8 8] \
              [list db 0 0xff] \
      ] \
      [list serper \
              [list long] \
              [list rate 0 0x7fff] \
              [list baud230400 0 0x000e] \
              [list baud38400 0 0x005c] \
              [list baud9600 0 0x0174] \
      ] \
      [list color \
              [list r 8 0xf] \
              [list g 4 0xf] \
              [list b 0 0xf] \
      ] \
      [list beamcon0 \
              [list harddis 14] \
              [list lpendis] \
              [list varvben] \
              [list loldis] \
              [list cscben] \
              [list varvsyen] \
              [list varhsyen] \
              [list varbeamen] \
              [list dual] \
              [list pal] \
              [list varcsyen] \
              [list blanken] \
              [list csytrue] \
              [list vsytrue] \
              [list hsytrue] \
      ] \
      [list potgo \
              [list outry 15] \
              [list datry] \
              [list outrx] \
              [list datrx] \
              [list outly] \
              [list datly] \
              [list outlx] \
              [list datlx] \
              [list start 0] \
      ] \
      [list bltcon0 \
              [list ash 12 0xf] \
              [list usea 11] \
              [list useb] \
              [list usec] \
              [list used] \
              [list lf 0 0xff] \
              [list start 12 0xf] \
      ] \
      [list bltcon1 \
              [list bsh 12 0xf ] \
              [list doff 7 ] \
              [list efe 4 ] \
              [list ife] \
              [list fci] \
              [list desc] \
              [list line] \
              [list texture 12 0xf] \
              [list sign 6] \
              [list sud 4] \
              [list sul] \
              [list aul] \
              [list sing] \
              [list oct  2 0x7] \
              [list oct0 2 0x6] \
              [list oct1 2 0x1] \
              [list oct2 2 0x3] \
              [list oct3 2 0x7] \
              [list oct4 2 0x5] \
              [list oct5 2 0x2] \
              [list oct6 2 0x0] \
              [list oct7 2 0x4] \
      ] \
      [list bltsize \
              [list h 6 0x3ff ] \
              [list w 0 0x3f] \
      ] \

