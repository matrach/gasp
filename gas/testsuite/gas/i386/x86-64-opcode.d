#as: -J
#objdump: -drw
#name: x86-64 opcode

.*: +file format elf64-x86-64

Disassembly of section .text:

0+000 <.text>:
[	 ]*0:[	 ]+41 ff 10[	 ]+callq[	 ]+\*\(%r8\)[	 ]*(#.*)*
[	 ]*3:[	 ]+ff 10[	 ]+callq[	 ]+\*\(%rax\)[	 ]*(#.*)*
[	 ]*5:[	 ]+41 ff 10[	 ]+callq[	 ]+\*\(%r8\)[	 ]*(#.*)*
[	 ]*8:[	 ]+ff 10[	 ]+callq[	 ]+\*\(%rax\)[	 ]*(#.*)*
[	 ]*a:[	 ]+cb[	 ]+lret[	 ]*(#.*)*
[	 ]*b:[	 ]+c3[	 ]+retq[	 ]*(#.*)*
[	 ]*c:[	 ]+cf[	 ]+iret[	 ]*(#.*)*
[	 ]*d:[	 ]+66 cf[	 ]+iretw[	 ]*(#.*)*
[	 ]*f:[	 ]+48 cf[	 ]+iretq[	 ]*(#.*)*
[	 ]*11:[	 ]+66 41 8c 08[	 ]+movw[	 ]+%cs,\(%r8\)[	 ]*(#.*)*
[	 ]*15:[	 ]+66 8c 08[	 ]+movw[	 ]+%cs,\(%rax\)[	 ]*(#.*)*
[	 ]*18:[	 ]+66 41 8c 10[	 ]+movw[	 ]+%ss,\(%r8\)[	 ]*(#.*)*
[	 ]*1c:[	 ]+66 8c 10[	 ]+movw[	 ]+%ss,\(%rax\)[	 ]*(#.*)*
[	 ]*1f:[	 ]+66 41 8c 20[	 ]+movw[	 ]+%fs,\(%r8\)[	 ]*(#.*)*
[	 ]*23:[	 ]+66 8c 20[	 ]+movw[	 ]+%fs,\(%rax\)[	 ]*(#.*)*
[	 ]*26:[	 ]+41 8c 08[	 ]+movl[	 ]+%cs,\(%r8\)[	 ]*(#.*)*
[	 ]*29:[	 ]+8c 08[	 ]+movl[	 ]+%cs,\(%rax\)[	 ]*(#.*)*
[	 ]*2b:[	 ]+41 8c 10[	 ]+movl[	 ]+%ss,\(%r8\)[	 ]*(#.*)*
[	 ]*2e:[	 ]+8c 10[	 ]+movl[	 ]+%ss,\(%rax\)[	 ]*(#.*)*
[	 ]*30:[	 ]+41 8c 20[	 ]+movl[	 ]+%fs,\(%r8\)[	 ]*(#.*)*
[	 ]*33:[	 ]+8c 20[	 ]+movl[	 ]+%fs,\(%rax\)[	 ]*(#.*)*
[	 ]*35:[	 ]+41 8e 10[	 ]+movl[	 ]+\(%r8\),%ss[	 ]*(#.*)*
[	 ]*38:[	 ]+8e 10[	 ]+movl[	 ]+\(%rax\),%ss[	 ]*(#.*)*
[	 ]*3a:[	 ]+41 8e 20[	 ]+movl[	 ]+\(%r8\),%fs[	 ]*(#.*)*
[	 ]*3d:[	 ]+8e 20[	 ]+movl[	 ]+\(%rax\),%fs[	 ]*(#.*)*
[	 ]*3f:[	 ]+41 c6 00 00[	 ]+movb[	 ]+\$0[x0]*,\(%r8\)[	 ]*(#.*)*
[	 ]*43:[	 ]+c6 00 00[	 ]+movb[	 ]+\$0[x0]*,\(%rax\)[	 ]*(#.*)*
[	 ]*46:[	 ]+66 41 c7 00 00 70[	 ]+movw[	 ]+\$0x7000,\(%r8\)[	 ]*(#.*)*
[	 ]*4c:[	 ]+66 c7 00 00 70[	 ]+movw[	 ]+\$0x7000,\(%rax\)[	 ]*(#.*)*
[	 ]*51:[	 ]+c7 00 00 00 00 70[	 ]+movl[	 ]+\$0x70000000,\(%rax\)[	 ]*(#.*)*
[	 ]*57:[	 ]+41 c6 00 00[	 ]+movb[	 ]+\$0[x0]*,\(%r8\)[	 ]*(#.*)*
[	 ]*5b:[	 ]+c6 00 00[	 ]+movb[	 ]+\$0[x0]*,\(%rax\)[	 ]*(#.*)*
[	 ]*5e:[	 ]+66 41 c7 00 00 70[	 ]+movw[	 ]+\$0x7000,\(%r8\)[	 ]*(#.*)*
[	 ]*64:[	 ]+66 c7 00 00 70[	 ]+movw[	 ]+\$0x7000,\(%rax\)[	 ]*(#.*)*
[	 ]*69:[	 ]+41 c7 00 00 00 00 70[	 ]+movl[	 ]+\$0x70000000,\(%r8\)[	 ]*(#.*)*
[	 ]*70:[	 ]+c7 00 00 00 00 70[	 ]+movl[	 ]+\$0x70000000,\(%rax\)[	 ]*(#.*)*
[	 ]*76:[	 ]+41 0f c3 00[	 ]+movnti[	 ]+%eax,\(%r8\)[	 ]*(#.*)*
[	 ]*7a:[	 ]+0f c3 00[	 ]+movnti[	 ]+%eax,\(%rax\)[	 ]*(#.*)*
[	 ]*7d:[	 ]+49 0f c3 00[	 ]+movnti[	 ]+%rax,\(%r8\)[	 ]*(#.*)*
[	 ]*81:[	 ]+48 0f c3 00[	 ]+movnti[	 ]+%rax,\(%rax\)[	 ]*(#.*)*
[	 ]*85:[	 ]+4d 0f c3 00[	 ]+movnti[	 ]+%r8,\(%r8\)[	 ]*(#.*)*
[	 ]*89:[	 ]+4c 0f c3 00[	 ]+movnti[	 ]+%r8,\(%rax\)[	 ]*(#.*)*
[	 ]*8d:[	 ]+41 f6 38[	 ]+idivb[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*90:[	 ]+f6 38[	 ]+idivb[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*92:[	 ]+66 41 f7 38[	 ]+idivw[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*96:[	 ]+66 f7 38[	 ]+idivw[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*99:[	 ]+41 f7 38[	 ]+idivl[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*9c:[	 ]+f7 38[	 ]+idivl[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*9e:[	 ]+49 f7 38[	 ]+idivq[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*a1:[	 ]+48 f7 38[	 ]+idivq[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*a4:[	 ]+41 f6 28[	 ]+imulb[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*a7:[	 ]+f6 28[	 ]+imulb[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*a9:[	 ]+66 41 f7 28[	 ]+imulw[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*ad:[	 ]+66 f7 28[	 ]+imulw[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*b0:[	 ]+41 f7 28[	 ]+imull[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*b3:[	 ]+f7 28[	 ]+imull[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*b5:[	 ]+49 f7 28[	 ]+imulq[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*b8:[	 ]+48 f7 28[	 ]+imulq[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*bb:[	 ]+66 41 0f 58 00[	 ]+addpd[	 ]+\(%r8\),%xmm0[	 ]*(#.*)*
[	 ]*c0:[	 ]+66 0f 58 00[	 ]+addpd[	 ]+\(%rax\),%xmm0[	 ]*(#.*)*
[	 ]*c4:[	 ]+66 45 0f 58 38[	 ]+addpd[	 ]+\(%r8\),%xmm15[	 ]*(#.*)*
[	 ]*c9:[	 ]+66 44 0f 58 38[	 ]+addpd[	 ]+\(%rax\),%xmm15[	 ]*(#.*)*
[	 ]*ce:[	 ]+66 45 0f 58 00[	 ]+addpd[	 ]+\(%r8\),%xmm8[	 ]*(#.*)*
[	 ]*d3:[	 ]+66 44 0f 58 00[	 ]+addpd[	 ]+\(%rax\),%xmm8[	 ]*(#.*)*
[	 ]*d8:[	 ]+66 41 0f 58 38[	 ]+addpd[	 ]+\(%r8\),%xmm7[	 ]*(#.*)*
[	 ]*dd:[	 ]+66 0f 58 38[	 ]+addpd[	 ]+\(%rax\),%xmm7[	 ]*(#.*)*
[	 ]*e1:[	 ]+66 0f 58 c0[	 ]+addpd[	 ]+%xmm0,%xmm0[	 ]*(#.*)*
[	 ]*e5:[	 ]+66 45 0f 58 ff[	 ]+addpd[	 ]+%xmm15,%xmm15[	 ]*(#.*)*
[	 ]*ea:[	 ]+66 45 0f 58 c7[	 ]+addpd[	 ]+%xmm15,%xmm8[	 ]*(#.*)*
[	 ]*ef:[	 ]+f2 49 0f 2d 00[	 ]+cvtsd2siq[	 ]+\(%r8\),%rax[	 ]*(#.*)*
[	 ]*f4:[	 ]+f2 48 0f 2d 00[	 ]+cvtsd2siq[	 ]+\(%rax\),%rax[	 ]*(#.*)*
[	 ]*f9:[	 ]+f2 4d 0f 2d 00[	 ]+cvtsd2siq[	 ]+\(%r8\),%r8[	 ]*(#.*)*
[	 ]*fe:[	 ]+f2 4c 0f 2d 00[	 ]+cvtsd2siq[	 ]+\(%rax\),%r8[	 ]*(#.*)*
[	 ]*103:[	 ]+f2 48 0f 2d c0[	 ]+cvtsd2siq[	 ]+%xmm0,%rax[	 ]*(#.*)*
[	 ]*108:[	 ]+f2 4d 0f 2d c7[	 ]+cvtsd2siq[	 ]+%xmm15,%r8[	 ]*(#.*)*
[	 ]*10d:[	 ]+f2 49 0f 2d c7[	 ]+cvtsd2siq[	 ]+%xmm15,%rax[	 ]*(#.*)*
[	 ]*112:[	 ]+f2 4d 0f 2d c0[	 ]+cvtsd2siq[	 ]+%xmm8,%r8[	 ]*(#.*)*
[	 ]*117:[	 ]+f2 49 0f 2d c0[	 ]+cvtsd2siq[	 ]+%xmm8,%rax[	 ]*(#.*)*
[	 ]*11c:[	 ]+f2 4c 0f 2d c7[	 ]+cvtsd2siq[	 ]+%xmm7,%r8[	 ]*(#.*)*
[	 ]*121:[	 ]+f2 48 0f 2d c7[	 ]+cvtsd2siq[	 ]+%xmm7,%rax[	 ]*(#.*)*
[	 ]*126:[	 ]+f2 4c 0f 2d c0[	 ]+cvtsd2siq[	 ]+%xmm0,%r8[	 ]*(#.*)*
[	 ]*12b:[	 ]+f2 49 0f 2c 00[	 ]+cvttsd2siq[	 ]+\(%r8\),%rax[	 ]*(#.*)*
[	 ]*130:[	 ]+f2 48 0f 2c 00[	 ]+cvttsd2siq[	 ]+\(%rax\),%rax[	 ]*(#.*)*
[	 ]*135:[	 ]+f2 4d 0f 2c 00[	 ]+cvttsd2siq[	 ]+\(%r8\),%r8[	 ]*(#.*)*
[	 ]*13a:[	 ]+f2 4c 0f 2c 00[	 ]+cvttsd2siq[	 ]+\(%rax\),%r8[	 ]*(#.*)*
[	 ]*13f:[	 ]+f2 48 0f 2c c0[	 ]+cvttsd2siq[	 ]+%xmm0,%rax[	 ]*(#.*)*
[	 ]*144:[	 ]+f2 4d 0f 2c c7[	 ]+cvttsd2siq[	 ]+%xmm15,%r8[	 ]*(#.*)*
[	 ]*149:[	 ]+f2 49 0f 2c c7[	 ]+cvttsd2siq[	 ]+%xmm15,%rax[	 ]*(#.*)*
[	 ]*14e:[	 ]+f2 4d 0f 2c c0[	 ]+cvttsd2siq[	 ]+%xmm8,%r8[	 ]*(#.*)*
[	 ]*153:[	 ]+f2 49 0f 2c c0[	 ]+cvttsd2siq[	 ]+%xmm8,%rax[	 ]*(#.*)*
[	 ]*158:[	 ]+f2 4c 0f 2c c7[	 ]+cvttsd2siq[	 ]+%xmm7,%r8[	 ]*(#.*)*
[	 ]*15d:[	 ]+f2 48 0f 2c c7[	 ]+cvttsd2siq[	 ]+%xmm7,%rax[	 ]*(#.*)*
[	 ]*162:[	 ]+f2 4c 0f 2c c0[	 ]+cvttsd2siq[	 ]+%xmm0,%r8[	 ]*(#.*)*
[	 ]*167:[	 ]+f3 49 0f 2d 00[	 ]+cvtss2siq[	 ]+\(%r8\),%rax[	 ]*(#.*)*
[	 ]*16c:[	 ]+f3 48 0f 2d 00[	 ]+cvtss2siq[	 ]+\(%rax\),%rax[	 ]*(#.*)*
[	 ]*171:[	 ]+f3 4d 0f 2d 00[	 ]+cvtss2siq[	 ]+\(%r8\),%r8[	 ]*(#.*)*
[	 ]*176:[	 ]+f3 4c 0f 2d 00[	 ]+cvtss2siq[	 ]+\(%rax\),%r8[	 ]*(#.*)*
[	 ]*17b:[	 ]+f3 48 0f 2d c0[	 ]+cvtss2siq[	 ]+%xmm0,%rax[	 ]*(#.*)*
[	 ]*180:[	 ]+f3 4d 0f 2d c7[	 ]+cvtss2siq[	 ]+%xmm15,%r8[	 ]*(#.*)*
[	 ]*185:[	 ]+f3 49 0f 2d c7[	 ]+cvtss2siq[	 ]+%xmm15,%rax[	 ]*(#.*)*
[	 ]*18a:[	 ]+f3 4d 0f 2d c0[	 ]+cvtss2siq[	 ]+%xmm8,%r8[	 ]*(#.*)*
[	 ]*18f:[	 ]+f3 49 0f 2d c0[	 ]+cvtss2siq[	 ]+%xmm8,%rax[	 ]*(#.*)*
[	 ]*194:[	 ]+f3 4c 0f 2d c7[	 ]+cvtss2siq[	 ]+%xmm7,%r8[	 ]*(#.*)*
[	 ]*199:[	 ]+f3 48 0f 2d c7[	 ]+cvtss2siq[	 ]+%xmm7,%rax[	 ]*(#.*)*
[	 ]*19e:[	 ]+f3 4c 0f 2d c0[	 ]+cvtss2siq[	 ]+%xmm0,%r8[	 ]*(#.*)*
[	 ]*1a3:[	 ]+f3 49 0f 2c 00[	 ]+cvttss2siq[	 ]+\(%r8\),%rax[	 ]*(#.*)*
[	 ]*1a8:[	 ]+f3 48 0f 2c 00[	 ]+cvttss2siq[	 ]+\(%rax\),%rax[	 ]*(#.*)*
[	 ]*1ad:[	 ]+f3 4d 0f 2c 00[	 ]+cvttss2siq[	 ]+\(%r8\),%r8[	 ]*(#.*)*
[	 ]*1b2:[	 ]+f3 4c 0f 2c 00[	 ]+cvttss2siq[	 ]+\(%rax\),%r8[	 ]*(#.*)*
[	 ]*1b7:[	 ]+f3 48 0f 2c c0[	 ]+cvttss2siq[	 ]+%xmm0,%rax[	 ]*(#.*)*
[	 ]*1bc:[	 ]+f3 4d 0f 2c c7[	 ]+cvttss2siq[	 ]+%xmm15,%r8[	 ]*(#.*)*
[	 ]*1c1:[	 ]+f3 49 0f 2c c7[	 ]+cvttss2siq[	 ]+%xmm15,%rax[	 ]*(#.*)*
[	 ]*1c6:[	 ]+f3 4d 0f 2c c0[	 ]+cvttss2siq[	 ]+%xmm8,%r8[	 ]*(#.*)*
[	 ]*1cb:[	 ]+f3 49 0f 2c c0[	 ]+cvttss2siq[	 ]+%xmm8,%rax[	 ]*(#.*)*
[	 ]*1d0:[	 ]+f3 4c 0f 2c c7[	 ]+cvttss2siq[	 ]+%xmm7,%r8[	 ]*(#.*)*
[	 ]*1d5:[	 ]+f3 48 0f 2c c7[	 ]+cvttss2siq[	 ]+%xmm7,%rax[	 ]*(#.*)*
[	 ]*1da:[	 ]+f3 4c 0f 2c c0[	 ]+cvttss2siq[	 ]+%xmm0,%r8[	 ]*(#.*)*
[	 ]*1df:[	 ]+f3 41 0f 2a 00[	 ]+cvtsi2ss[	 ]+\(%r8\),%xmm0[	 ]*(#.*)*
[	 ]*1e4:[	 ]+f3 0f 2a 00[	 ]+cvtsi2ss[	 ]+\(%rax\),%xmm0[	 ]*(#.*)*
[	 ]*1e8:[	 ]+f3 45 0f 2a 38[	 ]+cvtsi2ss[	 ]+\(%r8\),%xmm15[	 ]*(#.*)*
[	 ]*1ed:[	 ]+f3 44 0f 2a 38[	 ]+cvtsi2ss[	 ]+\(%rax\),%xmm15[	 ]*(#.*)*
[	 ]*1f2:[	 ]+f3 45 0f 2a 00[	 ]+cvtsi2ss[	 ]+\(%r8\),%xmm8[	 ]*(#.*)*
[	 ]*1f7:[	 ]+f3 44 0f 2a 00[	 ]+cvtsi2ss[	 ]+\(%rax\),%xmm8[	 ]*(#.*)*
[	 ]*1fc:[	 ]+f3 41 0f 2a 38[	 ]+cvtsi2ss[	 ]+\(%r8\),%xmm7[	 ]*(#.*)*
[	 ]*201:[	 ]+f3 0f 2a 38[	 ]+cvtsi2ss[	 ]+\(%rax\),%xmm7[	 ]*(#.*)*
[	 ]*205:[	 ]+f3 0f 2a c0[	 ]+cvtsi2ss[	 ]+%eax,%xmm0[	 ]*(#.*)*
[	 ]*209:[	 ]+f3 44 0f 2a f8[	 ]+cvtsi2ss[	 ]+%eax,%xmm15[	 ]*(#.*)*
[	 ]*20e:[	 ]+f3 44 0f 2a c0[	 ]+cvtsi2ss[	 ]+%eax,%xmm8[	 ]*(#.*)*
[	 ]*213:[	 ]+f3 0f 2a f8[	 ]+cvtsi2ss[	 ]+%eax,%xmm7[	 ]*(#.*)*
[	 ]*217:[	 ]+f3 41 0f 2a 00[	 ]+cvtsi2ss[	 ]+\(%r8\),%xmm0[	 ]*(#.*)*
[	 ]*21c:[	 ]+f3 0f 2a 00[	 ]+cvtsi2ss[	 ]+\(%rax\),%xmm0[	 ]*(#.*)*
[	 ]*220:[	 ]+f3 45 0f 2a 38[	 ]+cvtsi2ss[	 ]+\(%r8\),%xmm15[	 ]*(#.*)*
[	 ]*225:[	 ]+f3 44 0f 2a 38[	 ]+cvtsi2ss[	 ]+\(%rax\),%xmm15[	 ]*(#.*)*
[	 ]*22a:[	 ]+f3 45 0f 2a 00[	 ]+cvtsi2ss[	 ]+\(%r8\),%xmm8[	 ]*(#.*)*
[	 ]*22f:[	 ]+f3 44 0f 2a 00[	 ]+cvtsi2ss[	 ]+\(%rax\),%xmm8[	 ]*(#.*)*
[	 ]*234:[	 ]+f3 41 0f 2a 38[	 ]+cvtsi2ss[	 ]+\(%r8\),%xmm7[	 ]*(#.*)*
[	 ]*239:[	 ]+f3 0f 2a 38[	 ]+cvtsi2ss[	 ]+\(%rax\),%xmm7[	 ]*(#.*)*
[	 ]*23d:[	 ]+f2 41 0f 2a 00[	 ]+cvtsi2sd[	 ]+\(%r8\),%xmm0[	 ]*(#.*)*
[	 ]*242:[	 ]+f2 0f 2a 00[	 ]+cvtsi2sd[	 ]+\(%rax\),%xmm0[	 ]*(#.*)*
[	 ]*246:[	 ]+f2 45 0f 2a 38[	 ]+cvtsi2sd[	 ]+\(%r8\),%xmm15[	 ]*(#.*)*
[	 ]*24b:[	 ]+f2 44 0f 2a 38[	 ]+cvtsi2sd[	 ]+\(%rax\),%xmm15[	 ]*(#.*)*
[	 ]*250:[	 ]+f2 45 0f 2a 00[	 ]+cvtsi2sd[	 ]+\(%r8\),%xmm8[	 ]*(#.*)*
[	 ]*255:[	 ]+f2 44 0f 2a 00[	 ]+cvtsi2sd[	 ]+\(%rax\),%xmm8[	 ]*(#.*)*
[	 ]*25a:[	 ]+f2 41 0f 2a 38[	 ]+cvtsi2sd[	 ]+\(%r8\),%xmm7[	 ]*(#.*)*
[	 ]*25f:[	 ]+f2 0f 2a 38[	 ]+cvtsi2sd[	 ]+\(%rax\),%xmm7[	 ]*(#.*)*
[	 ]*263:[	 ]+f2 0f 2a c0[	 ]+cvtsi2sd[	 ]+%eax,%xmm0[	 ]*(#.*)*
[	 ]*267:[	 ]+f2 44 0f 2a f8[	 ]+cvtsi2sd[	 ]+%eax,%xmm15[	 ]*(#.*)*
[	 ]*26c:[	 ]+f2 44 0f 2a c0[	 ]+cvtsi2sd[	 ]+%eax,%xmm8[	 ]*(#.*)*
[	 ]*271:[	 ]+f2 0f 2a f8[	 ]+cvtsi2sd[	 ]+%eax,%xmm7[	 ]*(#.*)*
[	 ]*275:[	 ]+f2 41 0f 2a 00[	 ]+cvtsi2sd[	 ]+\(%r8\),%xmm0[	 ]*(#.*)*
[	 ]*27a:[	 ]+f2 0f 2a 00[	 ]+cvtsi2sd[	 ]+\(%rax\),%xmm0[	 ]*(#.*)*
[	 ]*27e:[	 ]+f2 45 0f 2a 38[	 ]+cvtsi2sd[	 ]+\(%r8\),%xmm15[	 ]*(#.*)*
[	 ]*283:[	 ]+f2 44 0f 2a 38[	 ]+cvtsi2sd[	 ]+\(%rax\),%xmm15[	 ]*(#.*)*
[	 ]*288:[	 ]+f2 45 0f 2a 00[	 ]+cvtsi2sd[	 ]+\(%r8\),%xmm8[	 ]*(#.*)*
[	 ]*28d:[	 ]+f2 44 0f 2a 00[	 ]+cvtsi2sd[	 ]+\(%rax\),%xmm8[	 ]*(#.*)*
[	 ]*292:[	 ]+f2 41 0f 2a 38[	 ]+cvtsi2sd[	 ]+\(%r8\),%xmm7[	 ]*(#.*)*
[	 ]*297:[	 ]+f2 0f 2a 38[	 ]+cvtsi2sd[	 ]+\(%rax\),%xmm7[	 ]*(#.*)*
[	 ]*29b:[	 ]+66 41 0f 6e 00[	 ]+movd[	 ]+\(%r8\),%xmm0[	 ]*(#.*)*
[	 ]*2a0:[	 ]+66 0f 6e 00[	 ]+movd[	 ]+\(%rax\),%xmm0[	 ]*(#.*)*
[	 ]*2a4:[	 ]+66 45 0f 6e 38[	 ]+movd[	 ]+\(%r8\),%xmm15[	 ]*(#.*)*
[	 ]*2a9:[	 ]+66 44 0f 6e 38[	 ]+movd[	 ]+\(%rax\),%xmm15[	 ]*(#.*)*
[	 ]*2ae:[	 ]+66 45 0f 6e 00[	 ]+movd[	 ]+\(%r8\),%xmm8[	 ]*(#.*)*
[	 ]*2b3:[	 ]+66 44 0f 6e 00[	 ]+movd[	 ]+\(%rax\),%xmm8[	 ]*(#.*)*
[	 ]*2b8:[	 ]+66 41 0f 6e 38[	 ]+movd[	 ]+\(%r8\),%xmm7[	 ]*(#.*)*
[	 ]*2bd:[	 ]+66 0f 6e 38[	 ]+movd[	 ]+\(%rax\),%xmm7[	 ]*(#.*)*
[	 ]*2c1:[	 ]+66 0f 6e c0[	 ]+movd[	 ]+%eax,%xmm0[	 ]*(#.*)*
[	 ]*2c5:[	 ]+66 44 0f 6e f8[	 ]+movd[	 ]+%eax,%xmm15[	 ]*(#.*)*
[	 ]*2ca:[	 ]+66 44 0f 6e c0[	 ]+movd[	 ]+%eax,%xmm8[	 ]*(#.*)*
[	 ]*2cf:[	 ]+66 0f 6e f8[	 ]+movd[	 ]+%eax,%xmm7[	 ]*(#.*)*
[	 ]*2d3:[	 ]+66 41 0f 7e 00[	 ]+movd[	 ]+%xmm0,\(%r8\)[	 ]*(#.*)*
[	 ]*2d8:[	 ]+66 0f 7e 00[	 ]+movd[	 ]+%xmm0,\(%rax\)[	 ]*(#.*)*
[	 ]*2dc:[	 ]+66 45 0f 7e 38[	 ]+movd[	 ]+%xmm15,\(%r8\)[	 ]*(#.*)*
[	 ]*2e1:[	 ]+66 44 0f 7e 38[	 ]+movd[	 ]+%xmm15,\(%rax\)[	 ]*(#.*)*
[	 ]*2e6:[	 ]+66 45 0f 7e 00[	 ]+movd[	 ]+%xmm8,\(%r8\)[	 ]*(#.*)*
[	 ]*2eb:[	 ]+66 44 0f 7e 00[	 ]+movd[	 ]+%xmm8,\(%rax\)[	 ]*(#.*)*
[	 ]*2f0:[	 ]+66 41 0f 7e 38[	 ]+movd[	 ]+%xmm7,\(%r8\)[	 ]*(#.*)*
[	 ]*2f5:[	 ]+66 0f 7e 38[	 ]+movd[	 ]+%xmm7,\(%rax\)[	 ]*(#.*)*
[	 ]*2f9:[	 ]+66 0f 7e c0[	 ]+movd[	 ]+%xmm0,%eax[	 ]*(#.*)*
[	 ]*2fd:[	 ]+66 44 0f 7e f8[	 ]+movd[	 ]+%xmm15,%eax[	 ]*(#.*)*
[	 ]*302:[	 ]+66 44 0f 7e c0[	 ]+movd[	 ]+%xmm8,%eax[	 ]*(#.*)*
[	 ]*307:[	 ]+66 0f 7e f8[	 ]+movd[	 ]+%xmm7,%eax[	 ]*(#.*)*
[	 ]*30b:[	 ]+f3 41 0f 7e 00[	 ]+movq[	 ]+\(%r8\),%xmm0[	 ]*(#.*)*
[	 ]*310:[	 ]+f3 0f 7e 00[	 ]+movq[	 ]+\(%rax\),%xmm0[	 ]*(#.*)*
[	 ]*314:[	 ]+f3 45 0f 7e 38[	 ]+movq[	 ]+\(%r8\),%xmm15[	 ]*(#.*)*
[	 ]*319:[	 ]+f3 44 0f 7e 38[	 ]+movq[	 ]+\(%rax\),%xmm15[	 ]*(#.*)*
[	 ]*31e:[	 ]+f3 45 0f 7e 00[	 ]+movq[	 ]+\(%r8\),%xmm8[	 ]*(#.*)*
[	 ]*323:[	 ]+f3 44 0f 7e 00[	 ]+movq[	 ]+\(%rax\),%xmm8[	 ]*(#.*)*
[	 ]*328:[	 ]+f3 41 0f 7e 38[	 ]+movq[	 ]+\(%r8\),%xmm7[	 ]*(#.*)*
[	 ]*32d:[	 ]+f3 0f 7e 38[	 ]+movq[	 ]+\(%rax\),%xmm7[	 ]*(#.*)*
[	 ]*331:[	 ]+f3 0f 7e c0[	 ]+movq[	 ]+%xmm0,%xmm0[	 ]*(#.*)*
[	 ]*335:[	 ]+f3 45 0f 7e ff[	 ]+movq[	 ]+%xmm15,%xmm15[	 ]*(#.*)*
[	 ]*33a:[	 ]+f3 45 0f 7e c7[	 ]+movq[	 ]+%xmm15,%xmm8[	 ]*(#.*)*
[	 ]*33f:[	 ]+f3 41 0f 7e ff[	 ]+movq[	 ]+%xmm15,%xmm7[	 ]*(#.*)*
[	 ]*344:[	 ]+f3 41 0f 7e c7[	 ]+movq[	 ]+%xmm15,%xmm0[	 ]*(#.*)*
[	 ]*349:[	 ]+f3 45 0f 7e f8[	 ]+movq[	 ]+%xmm8,%xmm15[	 ]*(#.*)*
[	 ]*34e:[	 ]+f3 45 0f 7e c0[	 ]+movq[	 ]+%xmm8,%xmm8[	 ]*(#.*)*
[	 ]*353:[	 ]+f3 41 0f 7e f8[	 ]+movq[	 ]+%xmm8,%xmm7[	 ]*(#.*)*
[	 ]*358:[	 ]+f3 41 0f 7e c0[	 ]+movq[	 ]+%xmm8,%xmm0[	 ]*(#.*)*
[	 ]*35d:[	 ]+f3 44 0f 7e ff[	 ]+movq[	 ]+%xmm7,%xmm15[	 ]*(#.*)*
[	 ]*362:[	 ]+f3 44 0f 7e c7[	 ]+movq[	 ]+%xmm7,%xmm8[	 ]*(#.*)*
[	 ]*367:[	 ]+f3 0f 7e ff[	 ]+movq[	 ]+%xmm7,%xmm7[	 ]*(#.*)*
[	 ]*36b:[	 ]+f3 0f 7e c7[	 ]+movq[	 ]+%xmm7,%xmm0[	 ]*(#.*)*
[	 ]*36f:[	 ]+f3 44 0f 7e f8[	 ]+movq[	 ]+%xmm0,%xmm15[	 ]*(#.*)*
[	 ]*374:[	 ]+f3 44 0f 7e c0[	 ]+movq[	 ]+%xmm0,%xmm8[	 ]*(#.*)*
[	 ]*379:[	 ]+f3 0f 7e f8[	 ]+movq[	 ]+%xmm0,%xmm7[	 ]*(#.*)*
[	 ]*37d:[	 ]+66 41 0f d6 00[	 ]+movq[	 ]+%xmm0,\(%r8\)[	 ]*(#.*)*
[	 ]*382:[	 ]+66 0f d6 00[	 ]+movq[	 ]+%xmm0,\(%rax\)[	 ]*(#.*)*
[	 ]*386:[	 ]+66 45 0f d6 38[	 ]+movq[	 ]+%xmm15,\(%r8\)[	 ]*(#.*)*
[	 ]*38b:[	 ]+66 44 0f d6 38[	 ]+movq[	 ]+%xmm15,\(%rax\)[	 ]*(#.*)*
[	 ]*390:[	 ]+66 45 0f d6 00[	 ]+movq[	 ]+%xmm8,\(%r8\)[	 ]*(#.*)*
[	 ]*395:[	 ]+66 44 0f d6 00[	 ]+movq[	 ]+%xmm8,\(%rax\)[	 ]*(#.*)*
[	 ]*39a:[	 ]+66 41 0f d6 38[	 ]+movq[	 ]+%xmm7,\(%r8\)[	 ]*(#.*)*
[	 ]*39f:[	 ]+41 0f 6e 00[	 ]+movd[	 ]+\(%r8\),%mm0[	 ]*(#.*)*
[	 ]*3a3:[	 ]+0f 6e 00[	 ]+movd[	 ]+\(%rax\),%mm0[	 ]*(#.*)*
[	 ]*3a6:[	 ]+41 0f 6e 38[	 ]+movd[	 ]+\(%r8\),%mm7[	 ]*(#.*)*
[	 ]*3aa:[	 ]+0f 6e 38[	 ]+movd[	 ]+\(%rax\),%mm7[	 ]*(#.*)*
[	 ]*3ad:[	 ]+0f 6e c0[	 ]+movd[	 ]+%eax,%mm0[	 ]*(#.*)*
[	 ]*3b0:[	 ]+0f 6e f8[	 ]+movd[	 ]+%eax,%mm7[	 ]*(#.*)*
[	 ]*3b3:[	 ]+41 0f 7e 00[	 ]+movd[	 ]+%mm0,\(%r8\)[	 ]*(#.*)*
[	 ]*3b7:[	 ]+0f 7e 00[	 ]+movd[	 ]+%mm0,\(%rax\)[	 ]*(#.*)*
[	 ]*3ba:[	 ]+41 0f 7e 38[	 ]+movd[	 ]+%mm7,\(%r8\)[	 ]*(#.*)*
[	 ]*3be:[	 ]+0f 7e 38[	 ]+movd[	 ]+%mm7,\(%rax\)[	 ]*(#.*)*
[	 ]*3c1:[	 ]+0f 7e c0[	 ]+movd[	 ]+%mm0,%eax[	 ]*(#.*)*
[	 ]*3c4:[	 ]+0f 7e f8[	 ]+movd[	 ]+%mm7,%eax[	 ]*(#.*)*
[	 ]*3c7:[	 ]+41 0f 6f 00[	 ]+movq[	 ]+\(%r8\),%mm0[	 ]*(#.*)*
[	 ]*3cb:[	 ]+0f 6f 00[	 ]+movq[	 ]+\(%rax\),%mm0[	 ]*(#.*)*
[	 ]*3ce:[	 ]+41 0f 6f 38[	 ]+movq[	 ]+\(%r8\),%mm7[	 ]*(#.*)*
[	 ]*3d2:[	 ]+0f 6f 38[	 ]+movq[	 ]+\(%rax\),%mm7[	 ]*(#.*)*
[	 ]*3d5:[	 ]+41 0f 7f 00[	 ]+movq[	 ]+%mm0,\(%r8\)[	 ]*(#.*)*
[	 ]*3d9:[	 ]+0f 7f 00[	 ]+movq[	 ]+%mm0,\(%rax\)[	 ]*(#.*)*
[	 ]*3dc:[	 ]+41 0f 7f 38[	 ]+movq[	 ]+%mm7,\(%r8\)[	 ]*(#.*)*
[	 ]*3e0:[	 ]+0f 7f 38[	 ]+movq[	 ]+%mm7,\(%rax\)[	 ]*(#.*)*
[	 ]*3e3:[	 ]+41 8f 00[	 ]+popq[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*3e6:[	 ]+8f 00[	 ]+popq[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*3e8:[	 ]+9d[	 ]+popfq[	 ]*(#.*)*
[	 ]*3e9:[	 ]+41 ff 30[	 ]+pushq[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*3ec:[	 ]+ff 30[	 ]+pushq[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*3ee:[	 ]+9c[	 ]+pushfq[	 ]*(#.*)*
[	 ]*3ef:[	 ]+0f 77[	 ]+emms[	 ]*(#.*)*
[	 ]*3f1:[	 ]+0f 0e[	 ]+femms[	 ]*(#.*)*
[	 ]*3f3:[	 ]+0f 08[	 ]+invd[	 ]*(#.*)*
[	 ]*3f5:[	 ]+41 0f 01 38[	 ]+invlpg[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*3f9:[	 ]+0f 01 38[	 ]+invlpg[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*3fc:[	 ]+41 0f 01 38[	 ]+invlpg[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*400:[	 ]+0f 01 38[	 ]+invlpg[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*403:[	 ]+41 0f 01 38[	 ]+invlpg[	 ]+\(%r8\)[	 ]*(#.*)*
[	 ]*407:[	 ]+0f 01 38[	 ]+invlpg[	 ]+\(%rax\)[	 ]*(#.*)*
[	 ]*40a:[	 ]+0f 00 c0[	 ]+sldt[	 ]+%eax[	 ]*(#.*)*
[	 ]*40d:[	 ]+e6 00[	 ]+out[	 ]+%al,\$0[x0]*[	 ]*(#.*)*
[	 ]*40f:[	 ]+66 e7 00[	 ]+out[	 ]+%ax,\$0[x0]*[	 ]*(#.*)*
[	 ]*412:[	 ]+e7 00[	 ]+out[	 ]+%eax,\$0[x0]*[	 ]*(#.*)*