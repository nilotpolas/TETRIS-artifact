`timescale 1ns/1ps

// latency = 5

// Fully pipeline PINI circuit in 5 clock cycles.
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
    rnd_2,
    rnd_1,
    rnd_3,
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
(* fv_type="sharing", fv_latency=5, fv_count=1 *)
output [d-1:0] o0;
(* fv_type="sharing", fv_latency=5, fv_count=1 *)
output [d-1:0] o1;
(* fv_type="sharing", fv_latency=5, fv_count=1 *)
output [d-1:0] o2;
(* fv_type="sharing", fv_latency=5, fv_count=1 *)
output [d-1:0] o3;
(* fv_type="sharing", fv_latency=5, fv_count=1 *)
output [d-1:0] o4;
(* fv_type="sharing", fv_latency=5, fv_count=1 *)
output [d-1:0] o5;
(* fv_type="sharing", fv_latency=5, fv_count=1 *)
output [d-1:0] o6;
(* fv_type="sharing", fv_latency=5, fv_count=1 *)
output [d-1:0] o7;
(* fv_type="random", fv_count=1, fv_rnd_count_0=3*(1*d*(d-1)/2), fv_rnd_lat_0=0  *)
input [3*(1*d*(d-1)/2)-1:0] rnd_0;
(* fv_type="random", fv_count=1, fv_rnd_count_0=1*(1*d*(d-1)/2), fv_rnd_lat_0=1  *)
input [1*(1*d*(d-1)/2)-1:0] rnd_1;
(* fv_type="random", fv_count=1, fv_rnd_count_0=1*(1*d*(d-1))+2*(1*d*(d-1)/2), fv_rnd_lat_0=2  *)
input [1*(1*d*(d-1))+2*(1*d*(d-1)/2)-1:0] rnd_2;
(* fv_type="random", fv_count=1, fv_rnd_count_0=1*(1*d*(d-1)/2), fv_rnd_lat_0=3  *)
input [1*(1*d*(d-1)/2)-1:0] rnd_3;
wire [d-1:0] i0_0;
wire [d-1:0] i0_1;
wire [d-1:0] i0_2;
wire [d-1:0] i1_0;
wire [d-1:0] i1_1;
wire [d-1:0] i1_2;
wire [d-1:0] i1_3;
wire [d-1:0] i2_0;
wire [d-1:0] i2_1;
wire [d-1:0] i2_2;
wire [d-1:0] i2_3;
wire [d-1:0] i2_4;
wire [d-1:0] i2_5;
wire [d-1:0] i3_0;
wire [d-1:0] i3_1;
wire [d-1:0] i3_2;
wire [d-1:0] i3_3;
wire [d-1:0] i3_4;
wire [d-1:0] i4_0;
wire [d-1:0] i4_1;
wire [d-1:0] i4_2;
wire [d-1:0] i5_0;
wire [d-1:0] i5_1;
wire [d-1:0] i5_2;
wire [d-1:0] i5_3;
wire [d-1:0] i6_0;
wire [d-1:0] i6_1;
wire [d-1:0] i6_2;
wire [d-1:0] i7_0;
wire [d-1:0] i7_1;
wire [d-1:0] i7_2;
wire [d-1:0] i7_3;
wire [d-1:0] i7_4;
wire [d-1:0] n1_1;
wire [d-1:0] n2_0;
wire [d-1:0] n3_1;
wire [d-1:0] n6_0;
wire [d-1:0] n7_1;
wire [d-1:0] nt0_2;
wire [d-1:0] nt1_2;
wire [d-1:0] nt2_2;
wire [d-1:0] nt3_3;
wire [d-1:0] nt4_3;
wire [d-1:0] nt5_4;
wire [d-1:0] o0_5;
wire [d-1:0] o1_4;
wire [d-1:0] o1_5;
wire [d-1:0] o2_2;
wire [d-1:0] o2_3;
wire [d-1:0] o2_4;
wire [d-1:0] o2_5;
wire [d-1:0] o3_3;
wire [d-1:0] o3_4;
wire [d-1:0] o3_5;
wire [d-1:0] o4_4;
wire [d-1:0] o4_5;
wire [d-1:0] o5_2;
wire [d-1:0] o5_3;
wire [d-1:0] o5_4;
wire [d-1:0] o5_5;
wire [d-1:0] o6_2;
wire [d-1:0] o6_3;
wire [d-1:0] o6_4;
wire [d-1:0] o6_5;
wire [d-1:0] o7_3;
wire [d-1:0] o7_4;
wire [d-1:0] o7_5;
wire [d-1:0] t0_2;
wire [d-1:0] t1_2;
wire [d-1:0] t2_2;
wire [d-1:0] t3_3;
wire [d-1:0] t4_3;
wire [d-1:0] t5_4;
wire [d-1:0] t6_4;
wire [d-1:0] t7_5;
assign i0_0 = i0;
assign i1_0 = i1;
assign i2_0 = i2;
assign i3_0 = i3;
assign i4_0 = i4;
assign i5_0 = i5;
assign i6_0 = i6;
assign i7_0 = i7;
assign o0 = o0_5;
assign o1 = o1_5;
assign o2 = o2_5;
assign o3 = o3_5;
assign o4 = o4_5;
assign o5 = o5_5;
assign o6 = o6_5;
assign o7 = o7_5;




MSKinv #(.d(d)) comp_n1_1 (
    .out(n1_1),
    .in(i1_1)
);
MSKinv #(.d(d)) comp_n2_0 (
    .out(n2_0),
    .in(i2_0)
);
MSKinv #(.d(d)) comp_n3_1 (
    .out(n3_1),
    .in(i3_1)
);
MSKinv #(.d(d)) comp_n6_0 (
    .out(n6_0),
    .in(i6_0)
);
MSKinv #(.d(d)) comp_n7_1 (
    .out(n7_1),
    .in(i7_1)
);
MSKand_hpc2_swapped #(.d(d)) comp_t0_2 (
    .out(t0_2),
    .rnd(rnd_0[0 +: 1*d*(d-1)/2]),
    .ina(n6_0),
    .inb(n7_1),
    .clk(clk)
);
MSKand_hpc2 #(.d(d)) comp_t1_2 (
    .out(t1_2),
    .rnd(rnd_0[1*(1*d*(d-1)/2) +: 1*d*(d-1)/2]),
    .ina(n3_1),
    .inb(n2_0),
    .clk(clk)
);
MSKand_hpc2_swapped #(.d(d)) comp_t2_2 (
    .out(t2_2),
    .rnd(rnd_0[2*(1*d*(d-1)/2) +: 1*d*(d-1)/2]),
    .ina(n2_0),
    .inb(n1_1),
    .clk(clk)
);
MSKinv #(.d(d)) comp_nt0_2 (
    .out(nt0_2),
    .in(t0_2)
);
MSKinv #(.d(d)) comp_nt1_2 (
    .out(nt1_2),
    .in(t1_2)
);
MSKinv #(.d(d)) comp_nt2_2 (
    .out(nt2_2),
    .in(t2_2)
);
MSKand_hpc3 #(.d(d)) comp_t3_3 (
    .out(t3_3),
    .rnd(rnd_2[0 +: 1*d*(d-1)]),
    .ina(nt0_2),
    .inb(nt1_2),
    .clk(clk)
);
MSKand_hpc2 #(.d(d)) comp_t4_3 (
    .out(t4_3),
    .rnd(rnd_1[0 +: 1*d*(d-1)/2]),
    .ina(nt1_2),
    .inb(n3_1),
    .clk(clk)
);
MSKinv #(.d(d)) comp_nt3_3 (
    .out(nt3_3),
    .in(t3_3)
);
MSKand_hpc2_swapped #(.d(d)) comp_t5_4 (
    .out(t5_4),
    .rnd(rnd_2[1*(1*d*(d-1)) +: 1*d*(d-1)/2]),
    .ina(nt2_2),
    .inb(nt3_3),
    .clk(clk)
);
MSKinv #(.d(d)) comp_nt4_3 (
    .out(nt4_3),
    .in(t4_3)
);
MSKinv #(.d(d)) comp_nt5_4 (
    .out(nt5_4),
    .in(t5_4)
);
MSKand_hpc2 #(.d(d)) comp_t6_4 (
    .out(t6_4),
    .rnd(rnd_2[1*(1*d*(d-1))+1*(1*d*(d-1)/2) +: 1*d*(d-1)/2]),
    .ina(nt3_3),
    .inb(nt0_2),
    .clk(clk)
);
MSKand_hpc2_swapped #(.d(d)) comp_t7_5 (
    .out(t7_5),
    .rnd(rnd_3[0 +: 1*d*(d-1)/2]),
    .ina(nt4_3),
    .inb(nt5_4),
    .clk(clk)
);
MSKxor #(.d(d)) comp_o6_2 (
    .out(o6_2),
    .ina(t0_2),
    .inb(i4_2)
);
MSKxor #(.d(d)) comp_o5_2 (
    .out(o5_2),
    .ina(t1_2),
    .inb(i0_2)
);
MSKxor #(.d(d)) comp_o2_2 (
    .out(o2_2),
    .ina(t2_2),
    .inb(i6_2)
);
MSKxor #(.d(d)) comp_o7_3 (
    .out(o7_3),
    .ina(t3_3),
    .inb(i5_3)
);
MSKxor #(.d(d)) comp_o0_5 (
    .out(o0_5),
    .ina(t7_5),
    .inb(i2_5)
);
MSKxor #(.d(d)) comp_o4_4 (
    .out(o4_4),
    .ina(t6_4),
    .inb(i3_4)
);
MSKxor #(.d(d)) comp_o1_4 (
    .out(o1_4),
    .ina(t5_4),
    .inb(i7_4)
);
MSKxor #(.d(d)) comp_o3_3 (
    .out(o3_3),
    .ina(t4_3),
    .inb(i1_3)
);
MSKreg #(.d(d)) reg_o3_3 (
    .in(o3_3),
    .out(o3_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o3_4 (
    .in(o3_4),
    .out(o3_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o7_3 (
    .in(o7_3),
    .out(o7_4),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o7_4 (
    .in(o7_4),
    .out(o7_5),
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
MSKreg #(.d(d)) reg_o2_4 (
    .in(o2_4),
    .out(o2_5),
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
MSKreg #(.d(d)) reg_o4_4 (
    .in(o4_4),
    .out(o4_5),
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
MSKreg #(.d(d)) reg_o5_4 (
    .in(o5_4),
    .out(o5_5),
    .clk(clk)
);
MSKreg #(.d(d)) reg_o1_4 (
    .in(o1_4),
    .out(o1_5),
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
endmodule
