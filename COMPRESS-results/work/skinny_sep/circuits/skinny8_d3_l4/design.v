`timescale 1ns/1ps

// latency = 4

// Fully pipeline PINI circuit in 4 clock cycles.
// This file has been automatically generated.
`ifdef FULLVERIF
(* fv_prop = "PINI", fv_strat = "composite", fv_order=d *)
`endif
module skinny8 # ( parameter d=3 ) (
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
(* fv_type="sharing", fv_latency=4, fv_count=1 *)
output [d-1:0] o0;
(* fv_type="sharing", fv_latency=4, fv_count=1 *)
output [d-1:0] o1;
(* fv_type="sharing", fv_latency=4, fv_count=1 *)
output [d-1:0] o2;
(* fv_type="sharing", fv_latency=4, fv_count=1 *)
output [d-1:0] o3;
(* fv_type="sharing", fv_latency=4, fv_count=1 *)
output [d-1:0] o4;
(* fv_type="sharing", fv_latency=4, fv_count=1 *)
output [d-1:0] o5;
(* fv_type="sharing", fv_latency=4, fv_count=1 *)
output [d-1:0] o6;
(* fv_type="sharing", fv_latency=4, fv_count=1 *)
output [d-1:0] o7;
(* fv_type="random", fv_count=1, fv_rnd_count_0=2*(1*d*(d-1))+2*(1*d*(d-1)/2), fv_rnd_lat_0=0  *)
input [2*(1*d*(d-1))+2*(1*d*(d-1)/2)-1:0] rnd_0;
(* fv_type="random", fv_count=1, fv_rnd_count_0=1*(1*d*(d-1))+1*(1*d*(d-1)/2), fv_rnd_lat_0=1  *)
input [1*(1*d*(d-1))+1*(1*d*(d-1)/2)-1:0] rnd_1;
(* fv_type="random", fv_count=1, fv_rnd_count_0=1*(1*d*(d-1))+1*(1*d*(d-1)/2), fv_rnd_lat_0=2  *)
input [1*(1*d*(d-1))+1*(1*d*(d-1)/2)-1:0] rnd_2;
wire [d-1:0] i0_0;
wire [d-1:0] i0_1;
wire [d-1:0] i1_0;
wire [d-1:0] i1_1;
wire [d-1:0] i1_2;
wire [d-1:0] i2_0;
wire [d-1:0] i2_1;
wire [d-1:0] i2_2;
wire [d-1:0] i2_3;
wire [d-1:0] i2_4;
wire [d-1:0] i3_0;
wire [d-1:0] i3_1;
wire [d-1:0] i3_2;
wire [d-1:0] i3_3;
wire [d-1:0] i4_0;
wire [d-1:0] i4_1;
wire [d-1:0] i5_0;
wire [d-1:0] i5_1;
wire [d-1:0] i5_2;
wire [d-1:0] i6_0;
wire [d-1:0] i6_1;
wire [d-1:0] i6_2;
wire [d-1:0] i7_0;
wire [d-1:0] i7_1;
wire [d-1:0] i7_2;
wire [d-1:0] i7_3;
wire [d-1:0] n1_1;
wire [d-1:0] n2_0;
wire [d-1:0] n2_1;
wire [d-1:0] n3_0;
wire [d-1:0] n3_1;
wire [d-1:0] n6_0;
wire [d-1:0] n7_0;
wire [d-1:0] n7_1;
wire [d-1:0] nt0_1;
wire [d-1:0] nt0_2;
wire [d-1:0] nt1_1;
wire [d-1:0] nt1_2;
wire [d-1:0] nt2_2;
wire [d-1:0] nt2_3;
wire [d-1:0] nt3_2;
wire [d-1:0] nt4_2;
wire [d-1:0] nt4_3;
wire [d-1:0] nt5_3;
wire [d-1:0] o0_4;
wire [d-1:0] o1_3;
wire [d-1:0] o1_4;
wire [d-1:0] o2_2;
wire [d-1:0] o2_3;
wire [d-1:0] o2_4;
wire [d-1:0] o3_2;
wire [d-1:0] o3_3;
wire [d-1:0] o3_4;
wire [d-1:0] o4_3;
wire [d-1:0] o4_4;
wire [d-1:0] o5_1;
wire [d-1:0] o5_2;
wire [d-1:0] o5_3;
wire [d-1:0] o5_4;
wire [d-1:0] o6_1;
wire [d-1:0] o6_2;
wire [d-1:0] o6_3;
wire [d-1:0] o6_4;
wire [d-1:0] o7_2;
wire [d-1:0] o7_3;
wire [d-1:0] o7_4;
wire [d-1:0] t0_1;
wire [d-1:0] t0_cross_1;
wire [d-1:0] t0_inner_0;
wire [d-1:0] t0_inner_1;
wire [d-1:0] t1_1;
wire [d-1:0] t1_cross_1;
wire [d-1:0] t1_inner_1;
wire [d-1:0] t2_2;
wire [d-1:0] t2_cross_2;
wire [d-1:0] t2_inner_1;
wire [d-1:0] t2_inner_2;
wire [d-1:0] t3_2;
wire [d-1:0] t3_cross_2;
wire [d-1:0] t3_inner_2;
wire [d-1:0] t4_2;
wire [d-1:0] t4_cross_2;
wire [d-1:0] t4_inner_1;
wire [d-1:0] t4_inner_2;
wire [d-1:0] t5_3;
wire [d-1:0] t5_cross_3;
wire [d-1:0] t5_inner_2;
wire [d-1:0] t5_inner_3;
wire [d-1:0] t6_3;
wire [d-1:0] t6_cross_3;
wire [d-1:0] t6_inner_2;
wire [d-1:0] t6_inner_3;
wire [d-1:0] t7_4;
wire [d-1:0] t7_cross_4;
wire [d-1:0] t7_inner_3;
wire [d-1:0] t7_inner_4;
assign i0_0 = i0;
assign i1_0 = i1;
assign i2_0 = i2;
assign i3_0 = i3;
assign i4_0 = i4;
assign i5_0 = i5;
assign i6_0 = i6;
assign i7_0 = i7;
assign o0 = o0_4;
assign o1 = o1_4;
assign o2 = o2_4;
assign o3 = o3_4;
assign o4 = o4_4;
assign o5 = o5_4;
assign o6 = o6_4;
assign o7 = o7_4;




MSKinv #(.d(d)) comp_n1_1 (
    .out(n1_1),
    .in(i1_1)
);
MSKinv #(.d(d)) comp_n2_0 (
    .out(n2_0),
    .in(i2_0)
);
MSKinv #(.d(d)) comp_n3_0 (
    .out(n3_0),
    .in(i3_0)
);
MSKinv #(.d(d)) comp_n6_0 (
    .out(n6_0),
    .in(i6_0)
);
MSKinv #(.d(d)) comp_n7_0 (
    .out(n7_0),
    .in(i7_0)
);
MSKxor #(.d(d)) comp_t0_1 (
    .out(t0_1),
    .ina(t0_cross_1),
    .inb(t0_inner_1)
);
MSKxor #(.d(d)) comp_t1_1 (
    .out(t1_1),
    .ina(t1_cross_1),
    .inb(t1_inner_1)
);
MSKxor #(.d(d)) comp_t2_2 (
    .out(t2_2),
    .ina(t2_cross_2),
    .inb(t2_inner_2)
);
MSKinv #(.d(d)) comp_nt0_1 (
    .out(nt0_1),
    .in(t0_1)
);
MSKinv #(.d(d)) comp_nt1_1 (
    .out(nt1_1),
    .in(t1_1)
);
MSKinv #(.d(d)) comp_nt2_2 (
    .out(nt2_2),
    .in(t2_2)
);
MSKxor #(.d(d)) comp_t3_2 (
    .out(t3_2),
    .ina(t3_cross_2),
    .inb(t3_inner_2)
);
MSKxor #(.d(d)) comp_t4_2 (
    .out(t4_2),
    .ina(t4_cross_2),
    .inb(t4_inner_2)
);
MSKinv #(.d(d)) comp_nt3_2 (
    .out(nt3_2),
    .in(t3_2)
);
MSKxor #(.d(d)) comp_t5_3 (
    .out(t5_3),
    .ina(t5_cross_3),
    .inb(t5_inner_3)
);
MSKinv #(.d(d)) comp_nt4_2 (
    .out(nt4_2),
    .in(t4_2)
);
MSKinv #(.d(d)) comp_nt5_3 (
    .out(nt5_3),
    .in(t5_3)
);
MSKxor #(.d(d)) comp_t6_3 (
    .out(t6_3),
    .ina(t6_cross_3),
    .inb(t6_inner_3)
);
MSKxor #(.d(d)) comp_t7_4 (
    .out(t7_4),
    .ina(t7_cross_4),
    .inb(t7_inner_4)
);
MSKxor #(.d(d)) comp_o6_1 (
    .out(o6_1),
    .ina(t0_1),
    .inb(i4_1)
);
MSKxor #(.d(d)) comp_o5_1 (
    .out(o5_1),
    .ina(t1_1),
    .inb(i0_1)
);
MSKxor #(.d(d)) comp_o2_2 (
    .out(o2_2),
    .ina(t2_2),
    .inb(i6_2)
);
MSKxor #(.d(d)) comp_o7_2 (
    .out(o7_2),
    .ina(t3_2),
    .inb(i5_2)
);
MSKxor #(.d(d)) comp_o0_4 (
    .out(o0_4),
    .ina(t7_4),
    .inb(i2_4)
);
MSKxor #(.d(d)) comp_o4_3 (
    .out(o4_3),
    .ina(t6_3),
    .inb(i3_3)
);
MSKxor #(.d(d)) comp_o1_3 (
    .out(o1_3),
    .ina(t5_3),
    .inb(i7_3)
);
MSKxor #(.d(d)) comp_o3_2 (
    .out(o3_2),
    .ina(t4_2),
    .inb(i1_2)
);
MSKand_hpc3_cross_er_swapped #(.d(d)) comp_t0_cross_1 (
    .out(t0_cross_1),
    .rnd(rnd_0[0 +: 1*d*(d-1)]),
    .ina(n6_0),
    .inb(n7_0),
    .inb_prev(n7_1),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t0_inner_0 (
    .out(t0_inner_0),
    .ina(n6_0),
    .inb(n7_0)
);
MSKand_hpc3_cross_er_swapped #(.d(d)) comp_t1_cross_1 (
    .out(t1_cross_1),
    .rnd(rnd_0[1*(1*d*(d-1)) +: 1*d*(d-1)]),
    .ina(n3_0),
    .inb(n2_0),
    .inb_prev(n2_1),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t1_inner_1 (
    .out(t1_inner_1),
    .ina(n3_1),
    .inb(n2_1)
);
MSKand_hpc2_cross_swapped #(.d(d)) comp_t2_cross_2 (
    .out(t2_cross_2),
    .rnd(rnd_0[2*(1*d*(d-1)) +: 1*d*(d-1)/2]),
    .ina(n2_0),
    .inb(n1_1),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t2_inner_1 (
    .out(t2_inner_1),
    .ina(n2_1),
    .inb(n1_1)
);
MSKand_hpc3_cross_er_swapped #(.d(d)) comp_t3_cross_2 (
    .out(t3_cross_2),
    .rnd(rnd_1[0 +: 1*d*(d-1)]),
    .ina(nt0_1),
    .inb(nt1_1),
    .inb_prev(nt1_2),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t3_inner_2 (
    .out(t3_inner_2),
    .ina(nt0_2),
    .inb(nt1_2)
);
MSKand_hpc2_cross #(.d(d)) comp_t4_cross_2 (
    .out(t4_cross_2),
    .rnd(rnd_0[2*(1*d*(d-1))+1*(1*d*(d-1)/2) +: 1*d*(d-1)/2]),
    .ina(nt1_1),
    .inb(n3_0),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t4_inner_1 (
    .out(t4_inner_1),
    .ina(nt1_1),
    .inb(n3_1)
);
MSKand_hpc3_cross_er #(.d(d)) comp_t5_cross_3 (
    .out(t5_cross_3),
    .rnd(rnd_2[0 +: 1*d*(d-1)]),
    .ina(nt2_2),
    .ina_prev(nt2_3),
    .inb(nt3_2),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t5_inner_2 (
    .out(t5_inner_2),
    .ina(nt2_2),
    .inb(nt3_2)
);
MSKand_hpc2_cross #(.d(d)) comp_t6_cross_3 (
    .out(t6_cross_3),
    .rnd(rnd_1[1*(1*d*(d-1)) +: 1*d*(d-1)/2]),
    .ina(nt3_2),
    .inb(nt0_1),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t6_inner_2 (
    .out(t6_inner_2),
    .ina(nt3_2),
    .inb(nt0_2)
);
MSKand_hpc2_cross_swapped #(.d(d)) comp_t7_cross_4 (
    .out(t7_cross_4),
    .rnd(rnd_2[1*(1*d*(d-1)) +: 1*d*(d-1)/2]),
    .ina(nt4_2),
    .inb(nt5_3),
    .clk(clk)
);
MSKand_sharewise #(.d(d)) comp_t7_inner_3 (
    .out(t7_inner_3),
    .ina(nt4_3),
    .inb(nt5_3)
);
MSKreg #(.d(d)) reg_o5_1 (
    .in(o5_1),
    .out(o5_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o5_2 (
    .in(o5_2),
    .out(o5_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o5_3 (
    .in(o5_3),
    .out(o5_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o3_2 (
    .in(o3_2),
    .out(o3_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o3_3 (
    .in(o3_3),
    .out(o3_4),
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
MSKreg #(.d(d)) reg_t0_inner_0 (
    .in(t0_inner_0),
    .out(t0_inner_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_nt4_2 (
    .in(nt4_2),
    .out(nt4_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i0_0 (
    .in(i0_0),
    .out(i0_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o2_2 (
    .in(o2_2),
    .out(o2_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o2_3 (
    .in(o2_3),
    .out(o2_4),
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
MSKreg #(.d(d)) reg_o4_3 (
    .in(o4_3),
    .out(o4_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t4_inner_1 (
    .in(t4_inner_1),
    .out(t4_inner_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o6_1 (
    .in(o6_1),
    .out(o6_2),
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
MSKreg #(.d(d)) reg_n7_0 (
    .in(n7_0),
    .out(n7_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o1_3 (
    .in(o1_3),
    .out(o1_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o7_2 (
    .in(o7_2),
    .out(o7_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o7_3 (
    .in(o7_3),
    .out(o7_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_nt2_2 (
    .in(nt2_2),
    .out(nt2_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t2_inner_1 (
    .in(t2_inner_1),
    .out(t2_inner_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_nt0_1 (
    .in(nt0_1),
    .out(nt0_2),
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
MSKreg #(.d(d)) reg_t5_inner_2 (
    .in(t5_inner_2),
    .out(t5_inner_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_n2_0 (
    .in(n2_0),
    .out(n2_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_n3_0 (
    .in(n3_0),
    .out(n3_1),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t6_inner_2 (
    .in(t6_inner_2),
    .out(t6_inner_3),
    .clk(clk)
);
MSKreg #(.d(d)) reg_i4_0 (
    .in(i4_0),
    .out(i4_1),
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
MSKreg #(.d(d)) reg_nt1_1 (
    .in(nt1_1),
    .out(nt1_2),
    .clk(clk)
);
MSKreg #(.d(d)) reg_t7_inner_3 (
    .in(t7_inner_3),
    .out(t7_inner_4),
    .clk(clk)
);
endmodule
