/* GIMP RGBA C-Source image dump (star.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[32 * 32 * 4 + 1];
} star = {
  32, 32, 4,
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000cPN*sL>\347j@*\354d?,\301\062\021\015\024\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000+\010\004\031}M\065\326\226[\071\377\247s\070"
  "\377\225k\063\377<\024\014d\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000~\\J\336\257zR\377vL'\377vV%\377yV*\377<\023\013d\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\215xv\000yW\060\337\256w\060\377"
  "\200b$\377kV\"\377v_)\377<\024\014d\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000S\065\063\212\313\252s\377\267\237\071\377\223~/\377|i+\377"
  "e[%\377;\024\015d\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\200cb\001D\034"
  "\025\207\250\223:\377\255\226\061\377\224\201,\377\213\201+\377o^%\377iO$\306"
  "\206jg\006\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000@\024\020\035\245\232i\327\313\262Y"
  "\377\270\235\070\377\277\257;\377\231\211-\377\226\211,\377\205t+\377\220"
  "\204,\377\221\206J\313\071\017\015\031\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\221\177}%\254\234\201"
  "\332\367\345\224\377\360\325b\377\305\242D\377\332\320O\377\253\243-\377"
  "\262\227*\377\263\251,\377\301\260+\377\335\313S\377\230\204M\321\235\203"
  "~\013\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\223\200\177\064\265\226^\377\376\335v\377\370\325`\377\374\341"
  "u\377\376\344q\377\335\320F\377\320\272\065\377\352\324>\377\343\316\070\377"
  "\344\277/\377\354\320Q\377\230\205-\303\071\023\015\030\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000zbK\255\345\310z\377\374"
  "\325a\377\367\324_\377\377\325i\377\377\325j\377\365\335O\377\333\276\064"
  "\377\351\322\065\377\353\325I\377\350\312\070\377\353\315\070\377\360\315O\377"
  "\233\200E\327zkY\003\037\004\002\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000w^@\314\367\326z\377\373\322X\377\357\312X\377\367\325j\377\377"
  "\325i\377\371\325X\377\344\311?\377\333\264/\377\366\322D\377\376\326Q\377"
  "\366\315C\377\375\320I\377\372\324Z\377\257\241;\377\201p\062\204=\022\014<"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000C\036\031Q\314\250\177\366\377\325"
  "u\377\373\322U\377\353\310X\377\355\325j\377\375\325i\377\375\325d\377\363"
  "\322H\377\343\273:\377\346\304\070\377\375\325S\377\376\325U\377\376\322M"
  "\377\375\326N\377\376\340[\377\352\327e\377\304\265^\352v^\070\314v_;\314"
  "dT?\070\"\003\000\023!\004\000\023RGC\012\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000C\027\020e\331\261u\377\377\325p\377\373\322]\377\357\277"
  "W\377\352\312j\377\361\314e\377\370\316_\377\375\326O\377\351\315N\377\330"
  "\255.\377\367\316C\377\376\325T\377\376\331Y\377\376\330Y\377\376\325Q\377"
  "\376\326[\377\376\345f\377\376\352k\377\375\352p\377\304\265[\377\265\246"
  "L\377\265\245T\377\232\212a\272E\026\020nI*(\060\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000D$\037U\316\266|\366\377\325i\377\374\322f\377\347\262"
  "G\377\347\274d\377\352\300_\377\356\304W\377\373\324R\377\367\324E\377\352"
  "\307B\377\343\267\062\377\364\312G\377\376\327Z\377\375\340i\377\375\346d"
  "\377\375\334[\377\376\333[\377\375\330X\377\375\340^\377\376\347f\377\376"
  "\347f\377\376\347i\377\360\336j\377\346\326k\377\272\252j\343XE/,\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000xZ:\314\370\320i\377\376\324_\377"
  "\363\300H\377\335\254U\377\352\300`\377\352\277V\377\352\306U\377\374\315"
  "L\377\376\325Q\377\360\301C\377\344\253*\377\367\305;\377\375\322X\377\376"
  "\344e\377\377\352j\377\377\353j\377\375\334X\377\376\333\\\377\365\305I\377"
  "\364\306C\377\374\312C\377\375\320B\377\375\333I\377\367\320@\377\177\\("
  "\336G)&\065\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000vV:\314\353\312j\377\373"
  "\325_\377\366\314`\377\334\250A\377\345\273U\377\352\277V\377\352\277V\377"
  "\355\300P\377\365\313B\377\374\324S\377\360\306A\377\353\261/\377\353\260"
  "\061\377\371\310G\377\373\337^\377\376\350f\377\377\352j\377\377\351j\377"
  "\372\343d\377\372\343c\377\346\266F\377\337\244\063\377\311\237\061\377\263"
  "\215\060\377pS.\365G(%Q\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\200dUs\311"
  "\250[\377\373\323j\377\377\325i\377\357\306M\377\314\236\067\377\346\273T"
  "\377\352\277O\377\353\276G\377\351\276?\377\366\315N\377\376\326\\\377\367"
  "\324K\377\334\241\064\377\352\256+\377\360\265-\377\362\311B\377\373\325M"
  "\377\375\337Z\377\375\337`\377\375\337`\377\376\327\\\377\363\310A\377\233"
  "v/\340E\027\017h]DBR\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\231\210"
  "\205\064\253\210H\377\356\303Z\377\374\323_\377\375\321c\377\357\271F\377"
  "\347\261=\377\350\270>\377\352\272<\377\351\272<\377\352\274:\377\363\302"
  "@\377\373\342U\377\370\327W\377\360\307F\377\351\263\066\377\343\245+\377"
  "\347\254*\377\347\260.\377\346\262/\377\360\304\071\377\362\311?\377\350\302"
  "\065\377\264\231;\375_FDk\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\225\202\201\025\224vY\260\340\271b\377\364\304T\377\376\323f\377"
  "\376\325e\377\363\311G\377\331\243\063\377\335\241-\377\337\252/\377\351\256"
  "+\377\351\265\060\377\356\302\063\377\362\320I\377\375\344d\377\374\342_\377"
  "\343\265>\377\317\226,\377\317\236*\377\326\236+\377\325\232+\377\300\223"
  "*\377\250\211+\377uX+\377K)'n\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\213ut\016\217pF\324\353\277Y\377\367\303V\377\374\323"
  "_\377\377\324g\377\373\323_\377\324\247\070\377\321\236+\377\326\246*\377"
  "\340\251*\377\350\254*\377\350\265*\377\354\273.\377\365\312=\377\367\325"
  "L\377\362\312@\377\277\221*\377\257y\060\377\270\206\061\377\264\213U\364T"
  "\060\033\304S\062'\234\206qn\016\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000xaEn\317\251X\377\352\300V\377\356\304N\377\365"
  "\313U\377\377\326^\377\371\321S\377\275\224;\377\301\212.\377\321\247,\377"
  "\331\252+\377\333\251*\377\344\253*\377\336\252*\377\335\256*\377\343\272"
  "\062\377\327\254+\377\240\205*\377E\031\022\234K\060.C\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000zf`\001[>\065a\311\244P\365\352\277J\377\352\275;\377\346\271*\377\356\306"
  ":\377\262\232\070\377\\>\033\377\204`#\377\302\231/\377\323\250*\377\325\252"
  "*\377\325\252*\377\324\252+\377\323\237*\377\300\225)\377\235w(\377H\032\023"
  "g\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000z`;k\276\227N\377\350\260"
  "B\377\336\253\062\377\314\245-\377\240\213G\377[\071-\315dLLf{]<\242\216k&"
  "\377\243}+\377\316\233-\377\320\236-\377\306\234,\377\242y,\377qP*\342bO"
  "L+\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000S=\065\000>\030\024[c?\063\256"
  "\205^C\377yP\062\350<\020\011\233\207lm\004\000\000\000\000iLG\000hID\000<\027\022=@\023\015\233"
  "@\022\015\233A\022\016\233:\016\013PeE@\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000o][\024\200jhdwb`M\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
};

