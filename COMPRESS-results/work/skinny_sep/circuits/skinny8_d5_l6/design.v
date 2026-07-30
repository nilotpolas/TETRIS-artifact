`timescale 1ns/1ps

// latency = 6

// Fully pipeline PINI circuit in 6 clock cycles.
// This file has been automatically generated.
`ifdef FULLVERIF
(* fv_prop = "PINI", fv_strat = "composite", fv_order=d *)
`endif
module skinny8 # ( parameter d=5 ) (
    clk,
    i0,
    i1,
    i2,
    i3,
    i4,
    i5,
    i6,
    i7,
    o0,
    o1,
    o2,
    o3,
    o4,
    o5,
    o6,
    o7,
    rnd_0,
    rnd_1,
    rnd_2,
    rnd_3,
    rnd_4,
);
`include "MSKand_hpc1.vh"
`include "MSKand_hpc2.vh"
`include "MSKand_hpc3.vh"
(* fv_type="clock" *)
input clk;
(* fv_type="sharing", fv_latency=0, fv_count=1 *)
input [d-1:0] i0;
(* fv_type="sharing", fv_latency=0, fv_count=1 *)
input [d-1:0] i1;
(* fv_type="sharing", fv_latency=0, fv_count=1 *)
input [d-1:0] i2;
(* fv_type="sharing", fv_latency=0, fv_count=1 *)
input [d-1:0] i3;
(* fv_type="sharing", fv_latency=0, fv_count=1 *)
input [d-1:0] i4;
(* fv_type="sharing", fv_latency=0, fv_count=1 *)
input [d-1:0] i5;
(* fv_type="sharing", fv_latency=0, fv_count=1 *)
input [d-1:0] i6;
(* fv_type="sharing", fv_latency=0, fv_count=1 *)
input [d-1:0] i7;
(* fv_type="sharing", fv_latency=6, fv_count=1 *)
output [d-1:0] o0;
(* fv_type="sharing", fv_latency=6, fv_count=1 *)
output [d-1:0] o1;
(* fv_type="sharing", fv_latency=6, fv_count=1 *)
output [d-1:0] o2;
(* fv_type="sharing", fv_latency=6, fv_count=1 *)
output [d-1:0] o3;
(* fv_type="sharing", fv_latency=6, fv_count=1 *)
output [d-1:0] o4;
(* fv_type="sharing", fv_latency=6, fv_count=1 *)
output [d-1:0] o5;
(* fv_type="sharing", fv_latency=6, fv_count=1 *)
output [d-1:0] o6;
(* fv_type="sharing", fv_latency=6, fv_count=1 *)
output [d-1:0] o7;
(* fv_type="random", fv_count=1, fv_rnd_count_0=1*(1*d*(d-1)/2), fv_rnd_lat_0=0  *)
input [1*(1*d*(d-1)/2)-1:0] rnd_0;
(* fv_type="random", fv_count=1, fv_rnd_count_0=2*(1*d*(d-1)/2), fv_rnd_lat_0=1  *)
input [2*(1*d*(d-1)/2)-1:0] rnd_1;
(* fv_type="random", fv_count=1, fv_rnd_count_0=2*(1*d*(d-1)/2), fv_rnd_lat_0=2  *)
input [2*(1*d*(d-1)/2)-1:0] rnd_2;
(* fv_type="random", fv_count=1, fv_rnd_count_0=2*(1*d*(d-1)/2), fv_rnd_lat_0=3  *)
input [2*(1*d*(d-1)/2)-1:0] rnd_3;
(* fv_type="random", fv_count=1, fv_rnd_count_0=1*(1*d*(d-1)/2), fv_rnd_lat_0=4  *)
input [1*(1*d*(d-1)/2)-1:0] rnd_4;
wire [d-1:0] i0_0;
wire [d-1:0] i0_1;
wire [d-1:0] i0_2;
wire [d-1:0] i0_3;
wire [d-1:0] i1_0;
wire [d-1:0] i1_1;
wire [d-1:0] i1_2;
wire [d-1:0] i1_3;
wire [d-1:0] i1_4;
wire [d-1:0] i2_0;
wire [d-1:0] i2_1;
wire [d-1:0] i2_2;
wire [d-1:0] i2_3;
wire [d-1:0] i2_4;
wire [d-1:0] i2_5;
wire [d-1:0] i2_6;
wire [d-1:0] i3_0;
wire [d-1:0] i3_1;
wire [d-1:0] i3_2;
wire [d-1:0] i3_3;
wire [d-1:0] i3_4;
wire [d-1:0] i3_5;
wire [d-1:0] i4_0;
wire [d-1:0] i4_1;
wire [d-1:0] i4_2;
wire [d-1:0] i5_0;
wire [d-1:0] i5_1;
wire [d-1:0] i5_2;
wire [d-1:0] i5_3;
wire [d-1:0] i5_4;
wire [d-1:0] i6_0;
wire [d-1:0] i6_1;
wire [d-1:0] i6_2;
wire [d-1:0] i6_3;
wire [d-1:0] i7_0;
wire [d-1:0] i7_1;
wire [d-1:0] i7_2;
wire [d-1:0] i7_3;
wire [d-1:0] i7_4;
wire [d-1:0] i7_5;
wire [d-1:0] n1_2;
wire [d-1:0] n2_1;
wire [d-1:0] n2_2;
wire [d-1:0] n3_2;
wire [d-1:0] n3_3;
wire [d-1:0] n6_0;
wire [d-1:0] n6_1;
wire [d-1:0] n7_1;
wire [d-1:0] nt0_2;
wire [d-1:0] nt0_3;
wire [d-1:0] nt0_4;
wire [d-1:0] nt1_3;
wire [d-1:0] nt1_4;
wire [d-1:0] nt2_3;
wire [d-1:0] nt2_4;
wire [d-1:0] nt3_4;
wire [d-1:0] nt4_4;
wire [d-1:0] nt4_5;
wire [d-1:0] nt5_5;
wire [d-1:0] o0_6;
wire [d-1:0] o1_5;
wire [d-1:0] o1_6;
wire [d-1:0] o2_3;
wire [d-1:0] o2_4;
wire [d-1:0] o2_5;
wire [d-1:0] o2_6;
wire [d-1:0] o3_4;
wire [d-1:0] o3_5;
wire [d-1:0] o3_6;
wire [d-1:0] o4_5;
wire [d-1:0] o4_6;
wire [d-1:0] o5_3;
wire [d-1:0] o5_4;
wire [d-1:0] o5_5;
wire [d-1:0] o5_6;
wire [d-1:0] o6_2;
wire [d-1:0] o6_3;
wire [d-1:0] o6_4;
wire [d-1:0] o6_5;
wire [d-1:0] o6_6;
wire [d-1:0] o7_4;
wire [d-1:0] o7_5;
wire [d-1:0] o7_6;
wire [d-1:0] t0_2;
wire [d-1:0] t0_cross_2;
wire [d-1:0] t0_inner_1;
wire [d-1:0] t0_inner_2;
wire [d-1:0] t1_3;
wire [d-1:0] t1_cross_3;
wire [d-1:0] t1_inner_2;
wire [d-1:0] t1_inner_3;
wire [d-1:0] t2_3;
wire [d-1:0] t2_cross_3;
wire [d-1:0] t2_inner_2;
wire [d-1:0] t2_inner_3;
wire [d-1:0] t3_4;
wire [d-1:0] t3_cross_4;
wire [d-1:0] t3_inner_4;
wire [d-1:0] t4_4;
wire [d-1:0] t4_cross_4;
wire [d-1:0] t4_inner_3;
wire [d-1:0] t4_inner_4;
wire [d-1:0] t5_5;
wire [d-1:0] t5_cross_5;
wire [d-1:0] t5_inner_4;
wire [d-1:0] t5_inner_5;
wire [d-1:0] t6_5;
wire [d-1:0] t6_cross_5;
wire [d-1:0] t6_inner_4;
wire [d-1:0] t6_inner_5;
wire [d-1:0] t7_6;
wire [d-1:0] t7_cross_6;
wire [d-1:0] t7_inner_5;
wire [d-1:0] t7_inner_6;
assign i0_0 = i0;
assign i1_0 = i1;
assign i2_0 = i2;
assign i3_0 = i3;
assign i4_0 = i4;
assign i5_0 = i5;
assign i6_0 = i6;
assign i7_0 = i7;
assign o0 = o0_6;
assign o1 = o1_6;
assign o2 = o2_6;
assign o3 = o3_6;
assign o4 = o4_6;
assign o5 = o5_6;
assign o6 = o6_6;
assign o7 = o7_6;




MSKinv #(.d(d)) comp_n1_2 (
    .out(n1_2),
    .in(i1_2)
);
MSKinv #(.d(d)) comp_n2_1 (
    .out(n2_1),
    .in(i2_1)
);
MSKinv #(.d(d)) comp_n3_2 (
    .out(n3_2),
    .in(i3_2)
);
MSKinv #(.d(d)) comp_n6_0 (
    .out(n6_0),
    .in(i6_0)
);
MSKinv #(.d(d)) comp_n7_1 (
    .out(n7_1),
    .in(i7_1)
);
MSKxor #(.d(d)) comp_t0_2 (
    .out(t0_2),
    .ina(t0_cross_2),
    .inb(t0_inner_2)
);
MSKxor #(.d(d)) comp_t1_3 (
    .out(t1_3),
    .ina(t1_cross_3),
    .inb(t1_inner_3)
);
MSKxor #(.d(d)) comp_t2_3 (
    .out(t2_3),
    .ina(t2_cross_3),
    .inb(t2_inner_3)
);
MSKinv #(.d(d)) comp_nt0_2 (
    .out(nt0_2),
    .in(t0_2)
);
MSKinv #(.d(d)) comp_nt1_3 (
    .out(nt1_3),
    .in(t1_3)
);
MSKinv #(.d(d)) comp_nt2_3 (
    .out(nt2_3),
    .in(t2_3)
);
MSKxor #(.d(d)) comp_t3_4 (
    .out(t3_4),
    .ina(t3_cross_4),
    .inb(t3_inner_4)
);
MSKxor #(.d(d)) comp_t4_4 (
    .out(t4_4),
    .ina(t4_cross_4),
    .inb(t4_inner_4)
);
MSKinv #(.d(d)) comp_nt3_4 (
    .out(nt3_4),
    .in(t3_4)
);
MSKxor #(.d(d)) comp_t5_5 (
    .out(t5_5),
    .ina(t5_cross_5),
    .inb(t5_inner_5)
);
MSKinv #(.d(d)) comp_nt4_4 (
    .out(nt4_4),
    .in(t4_4)
);
MSKinv #(.d(d)) comp_nt5_5 (
    .out(nt5_5),
    .in(t5_5)
);
MSKxor #(.d(d)) comp_t6_5 (
    .out(t6_5),
    .ina(t6_cross_5),
    .inb(t6_inner_5)
);
MSKxor #(.d(d)) comp_t7_6 (
    .out(t7_6),
    .ina(t7_cross_6),
    .inb(t7_inner_6)
);
MSKxor #(.d(d)) comp_o6_2 (
    .out(o6_2),
    .ina(t0_2),
    .inb(i4_2)
);
MSKxor #(.d(d)) comp_o5_3 (
    .out(o5_3),
    .ina(t1_3),
    .inb(i0_3)
);
MSKxor #(.d(d)) comp_o2_3 (
    .out(o2_3),
    .ina(t2_3),
    .inb(i6_3)
);
MSKxor #(.d(d)) comp_o7_4 (
    .out(o7_4),
    .ina(t3_4),
    .inb(i5_4)
);
MSKxor #(.d(d)) comp_o0_6 (
    .out(o0_6),
    .ina(t7_6),
    .inb(i2_6)
);
MSKxor #(.d(d)) comp_o4_5 (
    .out(o4_5),
    .ina(t6_5),
    .inb(i3_5)
);
MSKxor #(.d(d)) comp_o1_5 (
    .out(o1_5),
    .ina(t5_5),
    .inb(i7_5)
);
MSKxor #(.d(d)) comp_o3_4 (
    .out(o3_4),
    .ina(t4_4),
    .inb(i1_4)
);
MSKand_hpc2_cross_swapped #(.d(d)) comp_t0_cross_2 (
    .out(t0_cross_2),
    .rnd(rnd_0[0 +: 1*d*(d-1)/2]),
    .ina(n6_0),
    .inb(n7_1),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t0_inner_1 (
    .out(t0_inner_1),
    .ina(n6_1),
    .inb(n7_1)
);
MSKand_hpc2_cross #(.d(d)) comp_t1_cross_3 (
    .out(t1_cross_3),
    .rnd(rnd_1[0 +: 1*d*(d-1)/2]),
    .ina(n3_2),
    .inb(n2_1),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t1_inner_2 (
    .out(t1_inner_2),
    .ina(n3_2),
    .inb(n2_2)
);
MSKand_hpc2_cross_swapped #(.d(d)) comp_t2_cross_3 (
    .out(t2_cross_3),
    .rnd(rnd_1[1*(1*d*(d-1)/2) +: 1*d*(d-1)/2]),
    .ina(n2_1),
    .inb(n1_2),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t2_inner_2 (
    .out(t2_inner_2),
    .ina(n2_2),
    .inb(n1_2)
);
MSKand_hpc2_cross_swapped #(.d(d)) comp_t3_cross_4 (
    .out(t3_cross_4),
    .rnd(rnd_2[0 +: 1*d*(d-1)/2]),
    .ina(nt0_2),
    .inb(nt1_3),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t3_inner_4 (
    .out(t3_inner_4),
    .ina(nt0_4),
    .inb(nt1_4)
);
MSKand_hpc2_cross #(.d(d)) comp_t4_cross_4 (
    .out(t4_cross_4),
    .rnd(rnd_2[1*(1*d*(d-1)/2) +: 1*d*(d-1)/2]),
    .ina(nt1_3),
    .inb(n3_2),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t4_inner_3 (
    .out(t4_inner_3),
    .ina(nt1_3),
    .inb(n3_3)
);
MSKand_hpc2_cross_swapped #(.d(d)) comp_t5_cross_5 (
    .out(t5_cross_5),
    .rnd(rnd_3[0 +: 1*d*(d-1)/2]),
    .ina(nt2_3),
    .inb(nt3_4),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t5_inner_4 (
    .out(t5_inner_4),
    .ina(nt2_4),
    .inb(nt3_4)
);
MSKand_hpc2_cross #(.d(d)) comp_t6_cross_5 (
    .out(t6_cross_5),
    .rnd(rnd_3[1*(1*d*(d-1)/2) +: 1*d*(d-1)/2]),
    .ina(nt3_4),
    .inb(nt0_3),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t6_inner_4 (
    .out(t6_inner_4),
    .ina(nt3_4),
    .inb(nt0_4)
);
MSKand_hpc2_cross_swapped #(.d(d)) comp_t7_cross_6 (
    .out(t7_cross_6),
    .rnd(rnd_4[0 +: 1*d*(d-1)/2]),
    .ina(nt4_4),
    .inb(nt5_5),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t7_inner_5 (
    .out(t7_inner_5),
    .ina(nt4_5),
    .inb(nt5_5)
);
MSKreg #(.d(d)) reg_t0_inner_1 (
    .in(t0_inner_1),
    .out(t0_inner_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_nt1_3 (
    .in(nt1_3),
    .out(nt1_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o5_3 (
    .in(o5_3),
    .out(o5_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o5_4 (
    .in(o5_4),
    .out(o5_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o5_5 (
    .in(o5_5),
    .out(o5_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_nt4_4 (
    .in(nt4_4),
    .out(nt4_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_nt0_2 (
    .in(nt0_2),
    .out(nt0_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_nt0_3 (
    .in(nt0_3),
    .out(nt0_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i3_0 (
    .in(i3_0),
    .out(i3_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i3_1 (
    .in(i3_1),
    .out(i3_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i3_2 (
    .in(i3_2),
    .out(i3_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i3_3 (
    .in(i3_3),
    .out(i3_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i3_4 (
    .in(i3_4),
    .out(i3_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o6_2 (
    .in(o6_2),
    .out(o6_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o6_3 (
    .in(o6_3),
    .out(o6_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o6_4 (
    .in(o6_4),
    .out(o6_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o6_5 (
    .in(o6_5),
    .out(o6_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i4_0 (
    .in(i4_0),
    .out(i4_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i4_1 (
    .in(i4_1),
    .out(i4_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_nt2_3 (
    .in(nt2_3),
    .out(nt2_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o4_5 (
    .in(o4_5),
    .out(o4_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_n6_0 (
    .in(n6_0),
    .out(n6_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i0_0 (
    .in(i0_0),
    .out(i0_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i0_1 (
    .in(i0_1),
    .out(i0_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i0_2 (
    .in(i0_2),
    .out(i0_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t7_inner_5 (
    .in(t7_inner_5),
    .out(t7_inner_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o3_4 (
    .in(o3_4),
    .out(o3_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o3_5 (
    .in(o3_5),
    .out(o3_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t1_inner_2 (
    .in(t1_inner_2),
    .out(t1_inner_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t5_inner_4 (
    .in(t5_inner_4),
    .out(t5_inner_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o7_4 (
    .in(o7_4),
    .out(o7_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o7_5 (
    .in(o7_5),
    .out(o7_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o2_3 (
    .in(o2_3),
    .out(o2_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o2_4 (
    .in(o2_4),
    .out(o2_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o2_5 (
    .in(o2_5),
    .out(o2_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i6_0 (
    .in(i6_0),
    .out(i6_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i6_1 (
    .in(i6_1),
    .out(i6_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i6_2 (
    .in(i6_2),
    .out(i6_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i1_0 (
    .in(i1_0),
    .out(i1_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i1_1 (
    .in(i1_1),
    .out(i1_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i1_2 (
    .in(i1_2),
    .out(i1_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i1_3 (
    .in(i1_3),
    .out(i1_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i5_0 (
    .in(i5_0),
    .out(i5_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i5_1 (
    .in(i5_1),
    .out(i5_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i5_2 (
    .in(i5_2),
    .out(i5_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i5_3 (
    .in(i5_3),
    .out(i5_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_n3_2 (
    .in(n3_2),
    .out(n3_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t2_inner_2 (
    .in(t2_inner_2),
    .out(t2_inner_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i7_0 (
    .in(i7_0),
    .out(i7_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i7_1 (
    .in(i7_1),
    .out(i7_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i7_2 (
    .in(i7_2),
    .out(i7_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i7_3 (
    .in(i7_3),
    .out(i7_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i7_4 (
    .in(i7_4),
    .out(i7_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o1_5 (
    .in(o1_5),
    .out(o1_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t4_inner_3 (
    .in(t4_inner_3),
    .out(t4_inner_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i2_0 (
    .in(i2_0),
    .out(i2_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i2_1 (
    .in(i2_1),
    .out(i2_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i2_2 (
    .in(i2_2),
    .out(i2_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i2_3 (
    .in(i2_3),
    .out(i2_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i2_4 (
    .in(i2_4),
    .out(i2_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i2_5 (
    .in(i2_5),
    .out(i2_6),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t6_inner_4 (
    .in(t6_inner_4),
    .out(t6_inner_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_n2_1 (
    .in(n2_1),
    .out(n2_2),
    .clk(clk)
);
endmodule
