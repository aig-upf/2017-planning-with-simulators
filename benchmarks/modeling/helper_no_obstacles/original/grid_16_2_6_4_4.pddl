(define (problem grid_16_16_2_6_4_4)
  (:domain helper_fn_strips)
  (:objects
    cat_0 cat_1 cat_2 cat_3 - cat
    n_0_0 n_0_1 n_0_2 n_0_3 n_0_4 n_0_5 n_0_6 n_0_7 n_0_8 n_0_9 n_0_10 n_0_11 n_0_12 n_0_13 n_0_14 n_0_15 n_1_0 n_1_1 n_1_2 n_1_3 n_1_4 n_1_5 n_1_6 n_1_7 n_1_8 n_1_9 n_1_10 n_1_11 n_1_12 n_1_13 n_1_14 n_1_15 n_2_0 n_2_1 n_2_2 n_2_3 n_2_4 n_2_5 n_2_6 n_2_7 n_2_8 n_2_9 n_2_10 n_2_11 n_2_12 n_2_13 n_2_14 n_2_15 n_3_0 n_3_1 n_3_2 n_3_3 n_3_4 n_3_5 n_3_6 n_3_7 n_3_8 n_3_9 n_3_10 n_3_11 n_3_12 n_3_13 n_3_14 n_3_15 n_4_0 n_4_1 n_4_2 n_4_3 n_4_4 n_4_5 n_4_6 n_4_7 n_4_8 n_4_9 n_4_10 n_4_11 n_4_12 n_4_13 n_4_14 n_4_15 n_5_0 n_5_1 n_5_2 n_5_3 n_5_4 n_5_5 n_5_6 n_5_7 n_5_8 n_5_9 n_5_10 n_5_11 n_5_12 n_5_13 n_5_14 n_5_15 n_6_0 n_6_1 n_6_2 n_6_3 n_6_4 n_6_5 n_6_6 n_6_7 n_6_8 n_6_9 n_6_10 n_6_11 n_6_12 n_6_13 n_6_14 n_6_15 n_7_0 n_7_1 n_7_2 n_7_3 n_7_4 n_7_5 n_7_6 n_7_7 n_7_8 n_7_9 n_7_10 n_7_11 n_7_12 n_7_13 n_7_14 n_7_15 n_8_0 n_8_1 n_8_2 n_8_3 n_8_4 n_8_5 n_8_6 n_8_7 n_8_8 n_8_9 n_8_10 n_8_11 n_8_12 n_8_13 n_8_14 n_8_15 n_9_0 n_9_1 n_9_2 n_9_3 n_9_4 n_9_5 n_9_6 n_9_7 n_9_8 n_9_9 n_9_10 n_9_11 n_9_12 n_9_13 n_9_14 n_9_15 n_10_0 n_10_1 n_10_2 n_10_3 n_10_4 n_10_5 n_10_6 n_10_7 n_10_8 n_10_9 n_10_10 n_10_11 n_10_12 n_10_13 n_10_14 n_10_15 n_11_0 n_11_1 n_11_2 n_11_3 n_11_4 n_11_5 n_11_6 n_11_7 n_11_8 n_11_9 n_11_10 n_11_11 n_11_12 n_11_13 n_11_14 n_11_15 n_12_0 n_12_1 n_12_2 n_12_3 n_12_4 n_12_5 n_12_6 n_12_7 n_12_8 n_12_9 n_12_10 n_12_11 n_12_12 n_12_13 n_12_14 n_12_15 n_13_0 n_13_1 n_13_2 n_13_3 n_13_4 n_13_5 n_13_6 n_13_7 n_13_8 n_13_9 n_13_10 n_13_11 n_13_12 n_13_13 n_13_14 n_13_15 n_14_0 n_14_1 n_14_2 n_14_3 n_14_4 n_14_5 n_14_6 n_14_7 n_14_8 n_14_9 n_14_10 n_14_11 n_14_12 n_14_13 n_14_14 n_14_15 n_15_0 n_15_1 n_15_2 n_15_3 n_15_4 n_15_5 n_15_6 n_15_7 n_15_8 n_15_9 n_15_10 n_15_11 n_15_12 n_15_13 n_15_14 n_15_15 - node
  )
  (:init
    		(exit n_0_15)
		(exit n_15_15)
    		(edge n_0_0 n_1_0)
		(edge n_0_0 n_0_1)
		(edge n_0_1 n_1_1)
		(edge n_0_1 n_0_2)
		(edge n_0_1 n_0_0)
		(edge n_0_2 n_1_2)
		(edge n_0_2 n_0_3)
		(edge n_0_2 n_0_1)
		(edge n_0_3 n_1_3)
		(edge n_0_3 n_0_4)
		(edge n_0_3 n_0_2)
		(edge n_0_4 n_1_4)
		(edge n_0_4 n_0_5)
		(edge n_0_4 n_0_3)
		(edge n_0_5 n_1_5)
		(edge n_0_5 n_0_6)
		(edge n_0_5 n_0_4)
		(edge n_0_6 n_1_6)
		(edge n_0_6 n_0_7)
		(edge n_0_6 n_0_5)
		(edge n_0_7 n_1_7)
		(edge n_0_7 n_0_8)
		(edge n_0_7 n_0_6)
		(edge n_0_8 n_1_8)
		(edge n_0_8 n_0_9)
		(edge n_0_8 n_0_7)
		(edge n_0_9 n_1_9)
		(edge n_0_9 n_0_10)
		(edge n_0_9 n_0_8)
		(edge n_0_10 n_1_10)
		(edge n_0_10 n_0_11)
		(edge n_0_10 n_0_9)
		(edge n_0_11 n_1_11)
		(edge n_0_11 n_0_12)
		(edge n_0_11 n_0_10)
		(edge n_0_12 n_1_12)
		(edge n_0_12 n_0_13)
		(edge n_0_12 n_0_11)
		(edge n_0_13 n_1_13)
		(edge n_0_13 n_0_14)
		(edge n_0_13 n_0_12)
		(edge n_0_14 n_1_14)
		(edge n_0_14 n_0_15)
		(edge n_0_14 n_0_13)
		(edge n_0_15 n_1_15)
		(edge n_0_15 n_0_14)
		(edge n_1_0 n_0_0)
		(edge n_1_0 n_2_0)
		(edge n_1_0 n_1_1)
		(edge n_1_1 n_0_1)
		(edge n_1_1 n_2_1)
		(edge n_1_1 n_1_2)
		(edge n_1_1 n_1_0)
		(edge n_1_2 n_0_2)
		(edge n_1_2 n_2_2)
		(edge n_1_2 n_1_3)
		(edge n_1_2 n_1_1)
		(edge n_1_3 n_0_3)
		(edge n_1_3 n_2_3)
		(edge n_1_3 n_1_4)
		(edge n_1_3 n_1_2)
		(edge n_1_4 n_0_4)
		(edge n_1_4 n_2_4)
		(edge n_1_4 n_1_5)
		(edge n_1_4 n_1_3)
		(edge n_1_5 n_0_5)
		(edge n_1_5 n_2_5)
		(edge n_1_5 n_1_6)
		(edge n_1_5 n_1_4)
		(edge n_1_6 n_0_6)
		(edge n_1_6 n_2_6)
		(edge n_1_6 n_1_7)
		(edge n_1_6 n_1_5)
		(edge n_1_7 n_0_7)
		(edge n_1_7 n_2_7)
		(edge n_1_7 n_1_8)
		(edge n_1_7 n_1_6)
		(edge n_1_8 n_0_8)
		(edge n_1_8 n_2_8)
		(edge n_1_8 n_1_9)
		(edge n_1_8 n_1_7)
		(edge n_1_9 n_0_9)
		(edge n_1_9 n_2_9)
		(edge n_1_9 n_1_10)
		(edge n_1_9 n_1_8)
		(edge n_1_10 n_0_10)
		(edge n_1_10 n_2_10)
		(edge n_1_10 n_1_11)
		(edge n_1_10 n_1_9)
		(edge n_1_11 n_0_11)
		(edge n_1_11 n_2_11)
		(edge n_1_11 n_1_12)
		(edge n_1_11 n_1_10)
		(edge n_1_12 n_0_12)
		(edge n_1_12 n_2_12)
		(edge n_1_12 n_1_13)
		(edge n_1_12 n_1_11)
		(edge n_1_13 n_0_13)
		(edge n_1_13 n_2_13)
		(edge n_1_13 n_1_14)
		(edge n_1_13 n_1_12)
		(edge n_1_14 n_0_14)
		(edge n_1_14 n_2_14)
		(edge n_1_14 n_1_15)
		(edge n_1_14 n_1_13)
		(edge n_1_15 n_0_15)
		(edge n_1_15 n_2_15)
		(edge n_1_15 n_1_14)
		(edge n_2_0 n_1_0)
		(edge n_2_0 n_3_0)
		(edge n_2_0 n_2_1)
		(edge n_2_1 n_1_1)
		(edge n_2_1 n_3_1)
		(edge n_2_1 n_2_2)
		(edge n_2_1 n_2_0)
		(edge n_2_2 n_1_2)
		(edge n_2_2 n_3_2)
		(edge n_2_2 n_2_3)
		(edge n_2_2 n_2_1)
		(edge n_2_3 n_1_3)
		(edge n_2_3 n_3_3)
		(edge n_2_3 n_2_4)
		(edge n_2_3 n_2_2)
		(edge n_2_4 n_1_4)
		(edge n_2_4 n_3_4)
		(edge n_2_4 n_2_5)
		(edge n_2_4 n_2_3)
		(edge n_2_5 n_1_5)
		(edge n_2_5 n_3_5)
		(edge n_2_5 n_2_6)
		(edge n_2_5 n_2_4)
		(edge n_2_6 n_1_6)
		(edge n_2_6 n_3_6)
		(edge n_2_6 n_2_7)
		(edge n_2_6 n_2_5)
		(edge n_2_7 n_1_7)
		(edge n_2_7 n_3_7)
		(edge n_2_7 n_2_8)
		(edge n_2_7 n_2_6)
		(edge n_2_8 n_1_8)
		(edge n_2_8 n_3_8)
		(edge n_2_8 n_2_9)
		(edge n_2_8 n_2_7)
		(edge n_2_9 n_1_9)
		(edge n_2_9 n_3_9)
		(edge n_2_9 n_2_10)
		(edge n_2_9 n_2_8)
		(edge n_2_10 n_1_10)
		(edge n_2_10 n_3_10)
		(edge n_2_10 n_2_11)
		(edge n_2_10 n_2_9)
		(edge n_2_11 n_1_11)
		(edge n_2_11 n_3_11)
		(edge n_2_11 n_2_12)
		(edge n_2_11 n_2_10)
		(edge n_2_12 n_1_12)
		(edge n_2_12 n_3_12)
		(edge n_2_12 n_2_13)
		(edge n_2_12 n_2_11)
		(edge n_2_13 n_1_13)
		(edge n_2_13 n_3_13)
		(edge n_2_13 n_2_14)
		(edge n_2_13 n_2_12)
		(edge n_2_14 n_1_14)
		(edge n_2_14 n_3_14)
		(edge n_2_14 n_2_15)
		(edge n_2_14 n_2_13)
		(edge n_2_15 n_1_15)
		(edge n_2_15 n_3_15)
		(edge n_2_15 n_2_14)
		(edge n_3_0 n_2_0)
		(edge n_3_0 n_4_0)
		(edge n_3_0 n_3_1)
		(edge n_3_1 n_2_1)
		(edge n_3_1 n_4_1)
		(edge n_3_1 n_3_2)
		(edge n_3_1 n_3_0)
		(edge n_3_2 n_2_2)
		(edge n_3_2 n_4_2)
		(edge n_3_2 n_3_3)
		(edge n_3_2 n_3_1)
		(edge n_3_3 n_2_3)
		(edge n_3_3 n_4_3)
		(edge n_3_3 n_3_4)
		(edge n_3_3 n_3_2)
		(edge n_3_4 n_2_4)
		(edge n_3_4 n_4_4)
		(edge n_3_4 n_3_5)
		(edge n_3_4 n_3_3)
		(edge n_3_5 n_2_5)
		(edge n_3_5 n_4_5)
		(edge n_3_5 n_3_6)
		(edge n_3_5 n_3_4)
		(edge n_3_6 n_2_6)
		(edge n_3_6 n_4_6)
		(edge n_3_6 n_3_7)
		(edge n_3_6 n_3_5)
		(edge n_3_7 n_2_7)
		(edge n_3_7 n_4_7)
		(edge n_3_7 n_3_8)
		(edge n_3_7 n_3_6)
		(edge n_3_8 n_2_8)
		(edge n_3_8 n_4_8)
		(edge n_3_8 n_3_9)
		(edge n_3_8 n_3_7)
		(edge n_3_9 n_2_9)
		(edge n_3_9 n_4_9)
		(edge n_3_9 n_3_10)
		(edge n_3_9 n_3_8)
		(edge n_3_10 n_2_10)
		(edge n_3_10 n_4_10)
		(edge n_3_10 n_3_11)
		(edge n_3_10 n_3_9)
		(edge n_3_11 n_2_11)
		(edge n_3_11 n_4_11)
		(edge n_3_11 n_3_12)
		(edge n_3_11 n_3_10)
		(edge n_3_12 n_2_12)
		(edge n_3_12 n_4_12)
		(edge n_3_12 n_3_13)
		(edge n_3_12 n_3_11)
		(edge n_3_13 n_2_13)
		(edge n_3_13 n_4_13)
		(edge n_3_13 n_3_14)
		(edge n_3_13 n_3_12)
		(edge n_3_14 n_2_14)
		(edge n_3_14 n_4_14)
		(edge n_3_14 n_3_15)
		(edge n_3_14 n_3_13)
		(edge n_3_15 n_2_15)
		(edge n_3_15 n_4_15)
		(edge n_3_15 n_3_14)
		(edge n_4_0 n_3_0)
		(edge n_4_0 n_5_0)
		(edge n_4_0 n_4_1)
		(edge n_4_1 n_3_1)
		(edge n_4_1 n_5_1)
		(edge n_4_1 n_4_2)
		(edge n_4_1 n_4_0)
		(edge n_4_2 n_3_2)
		(edge n_4_2 n_5_2)
		(edge n_4_2 n_4_3)
		(edge n_4_2 n_4_1)
		(edge n_4_3 n_3_3)
		(edge n_4_3 n_5_3)
		(edge n_4_3 n_4_4)
		(edge n_4_3 n_4_2)
		(edge n_4_4 n_3_4)
		(edge n_4_4 n_5_4)
		(edge n_4_4 n_4_5)
		(edge n_4_4 n_4_3)
		(edge n_4_5 n_3_5)
		(edge n_4_5 n_5_5)
		(edge n_4_5 n_4_6)
		(edge n_4_5 n_4_4)
		(edge n_4_6 n_3_6)
		(edge n_4_6 n_5_6)
		(edge n_4_6 n_4_7)
		(edge n_4_6 n_4_5)
		(edge n_4_7 n_3_7)
		(edge n_4_7 n_5_7)
		(edge n_4_7 n_4_8)
		(edge n_4_7 n_4_6)
		(edge n_4_8 n_3_8)
		(edge n_4_8 n_5_8)
		(edge n_4_8 n_4_9)
		(edge n_4_8 n_4_7)
		(edge n_4_9 n_3_9)
		(edge n_4_9 n_5_9)
		(edge n_4_9 n_4_10)
		(edge n_4_9 n_4_8)
		(edge n_4_10 n_3_10)
		(edge n_4_10 n_5_10)
		(edge n_4_10 n_4_11)
		(edge n_4_10 n_4_9)
		(edge n_4_11 n_3_11)
		(edge n_4_11 n_5_11)
		(edge n_4_11 n_4_12)
		(edge n_4_11 n_4_10)
		(edge n_4_12 n_3_12)
		(edge n_4_12 n_5_12)
		(edge n_4_12 n_4_13)
		(edge n_4_12 n_4_11)
		(edge n_4_13 n_3_13)
		(edge n_4_13 n_5_13)
		(edge n_4_13 n_4_14)
		(edge n_4_13 n_4_12)
		(edge n_4_14 n_3_14)
		(edge n_4_14 n_5_14)
		(edge n_4_14 n_4_15)
		(edge n_4_14 n_4_13)
		(edge n_4_15 n_3_15)
		(edge n_4_15 n_5_15)
		(edge n_4_15 n_4_14)
		(edge n_5_0 n_4_0)
		(edge n_5_0 n_6_0)
		(edge n_5_0 n_5_1)
		(edge n_5_1 n_4_1)
		(edge n_5_1 n_6_1)
		(edge n_5_1 n_5_2)
		(edge n_5_1 n_5_0)
		(edge n_5_2 n_4_2)
		(edge n_5_2 n_6_2)
		(edge n_5_2 n_5_3)
		(edge n_5_2 n_5_1)
		(edge n_5_3 n_4_3)
		(edge n_5_3 n_6_3)
		(edge n_5_3 n_5_4)
		(edge n_5_3 n_5_2)
		(edge n_5_4 n_4_4)
		(edge n_5_4 n_6_4)
		(edge n_5_4 n_5_5)
		(edge n_5_4 n_5_3)
		(edge n_5_5 n_4_5)
		(edge n_5_5 n_6_5)
		(edge n_5_5 n_5_6)
		(edge n_5_5 n_5_4)
		(edge n_5_6 n_4_6)
		(edge n_5_6 n_6_6)
		(edge n_5_6 n_5_7)
		(edge n_5_6 n_5_5)
		(edge n_5_7 n_4_7)
		(edge n_5_7 n_6_7)
		(edge n_5_7 n_5_8)
		(edge n_5_7 n_5_6)
		(edge n_5_8 n_4_8)
		(edge n_5_8 n_6_8)
		(edge n_5_8 n_5_9)
		(edge n_5_8 n_5_7)
		(edge n_5_9 n_4_9)
		(edge n_5_9 n_6_9)
		(edge n_5_9 n_5_10)
		(edge n_5_9 n_5_8)
		(edge n_5_10 n_4_10)
		(edge n_5_10 n_6_10)
		(edge n_5_10 n_5_11)
		(edge n_5_10 n_5_9)
		(edge n_5_11 n_4_11)
		(edge n_5_11 n_6_11)
		(edge n_5_11 n_5_12)
		(edge n_5_11 n_5_10)
		(edge n_5_12 n_4_12)
		(edge n_5_12 n_6_12)
		(edge n_5_12 n_5_13)
		(edge n_5_12 n_5_11)
		(edge n_5_13 n_4_13)
		(edge n_5_13 n_6_13)
		(edge n_5_13 n_5_14)
		(edge n_5_13 n_5_12)
		(edge n_5_14 n_4_14)
		(edge n_5_14 n_6_14)
		(edge n_5_14 n_5_15)
		(edge n_5_14 n_5_13)
		(edge n_5_15 n_4_15)
		(edge n_5_15 n_6_15)
		(edge n_5_15 n_5_14)
		(edge n_6_0 n_5_0)
		(edge n_6_0 n_7_0)
		(edge n_6_0 n_6_1)
		(edge n_6_1 n_5_1)
		(edge n_6_1 n_7_1)
		(edge n_6_1 n_6_2)
		(edge n_6_1 n_6_0)
		(edge n_6_2 n_5_2)
		(edge n_6_2 n_7_2)
		(edge n_6_2 n_6_3)
		(edge n_6_2 n_6_1)
		(edge n_6_3 n_5_3)
		(edge n_6_3 n_7_3)
		(edge n_6_3 n_6_4)
		(edge n_6_3 n_6_2)
		(edge n_6_4 n_5_4)
		(edge n_6_4 n_7_4)
		(edge n_6_4 n_6_5)
		(edge n_6_4 n_6_3)
		(edge n_6_5 n_5_5)
		(edge n_6_5 n_7_5)
		(edge n_6_5 n_6_6)
		(edge n_6_5 n_6_4)
		(edge n_6_6 n_5_6)
		(edge n_6_6 n_7_6)
		(edge n_6_6 n_6_7)
		(edge n_6_6 n_6_5)
		(edge n_6_7 n_5_7)
		(edge n_6_7 n_7_7)
		(edge n_6_7 n_6_8)
		(edge n_6_7 n_6_6)
		(edge n_6_8 n_5_8)
		(edge n_6_8 n_7_8)
		(edge n_6_8 n_6_9)
		(edge n_6_8 n_6_7)
		(edge n_6_9 n_5_9)
		(edge n_6_9 n_7_9)
		(edge n_6_9 n_6_10)
		(edge n_6_9 n_6_8)
		(edge n_6_10 n_5_10)
		(edge n_6_10 n_7_10)
		(edge n_6_10 n_6_11)
		(edge n_6_10 n_6_9)
		(edge n_6_11 n_5_11)
		(edge n_6_11 n_7_11)
		(edge n_6_11 n_6_12)
		(edge n_6_11 n_6_10)
		(edge n_6_12 n_5_12)
		(edge n_6_12 n_7_12)
		(edge n_6_12 n_6_13)
		(edge n_6_12 n_6_11)
		(edge n_6_13 n_5_13)
		(edge n_6_13 n_7_13)
		(edge n_6_13 n_6_14)
		(edge n_6_13 n_6_12)
		(edge n_6_14 n_5_14)
		(edge n_6_14 n_7_14)
		(edge n_6_14 n_6_15)
		(edge n_6_14 n_6_13)
		(edge n_6_15 n_5_15)
		(edge n_6_15 n_7_15)
		(edge n_6_15 n_6_14)
		(edge n_7_0 n_6_0)
		(edge n_7_0 n_8_0)
		(edge n_7_0 n_7_1)
		(edge n_7_1 n_6_1)
		(edge n_7_1 n_8_1)
		(edge n_7_1 n_7_2)
		(edge n_7_1 n_7_0)
		(edge n_7_2 n_6_2)
		(edge n_7_2 n_8_2)
		(edge n_7_2 n_7_3)
		(edge n_7_2 n_7_1)
		(edge n_7_3 n_6_3)
		(edge n_7_3 n_8_3)
		(edge n_7_3 n_7_4)
		(edge n_7_3 n_7_2)
		(edge n_7_4 n_6_4)
		(edge n_7_4 n_8_4)
		(edge n_7_4 n_7_5)
		(edge n_7_4 n_7_3)
		(edge n_7_5 n_6_5)
		(edge n_7_5 n_8_5)
		(edge n_7_5 n_7_6)
		(edge n_7_5 n_7_4)
		(edge n_7_6 n_6_6)
		(edge n_7_6 n_8_6)
		(edge n_7_6 n_7_7)
		(edge n_7_6 n_7_5)
		(edge n_7_7 n_6_7)
		(edge n_7_7 n_8_7)
		(edge n_7_7 n_7_8)
		(edge n_7_7 n_7_6)
		(edge n_7_8 n_6_8)
		(edge n_7_8 n_8_8)
		(edge n_7_8 n_7_9)
		(edge n_7_8 n_7_7)
		(edge n_7_9 n_6_9)
		(edge n_7_9 n_8_9)
		(edge n_7_9 n_7_10)
		(edge n_7_9 n_7_8)
		(edge n_7_10 n_6_10)
		(edge n_7_10 n_8_10)
		(edge n_7_10 n_7_11)
		(edge n_7_10 n_7_9)
		(edge n_7_11 n_6_11)
		(edge n_7_11 n_8_11)
		(edge n_7_11 n_7_12)
		(edge n_7_11 n_7_10)
		(edge n_7_12 n_6_12)
		(edge n_7_12 n_8_12)
		(edge n_7_12 n_7_13)
		(edge n_7_12 n_7_11)
		(edge n_7_13 n_6_13)
		(edge n_7_13 n_8_13)
		(edge n_7_13 n_7_14)
		(edge n_7_13 n_7_12)
		(edge n_7_14 n_6_14)
		(edge n_7_14 n_8_14)
		(edge n_7_14 n_7_15)
		(edge n_7_14 n_7_13)
		(edge n_7_15 n_6_15)
		(edge n_7_15 n_8_15)
		(edge n_7_15 n_7_14)
		(edge n_8_0 n_7_0)
		(edge n_8_0 n_9_0)
		(edge n_8_0 n_8_1)
		(edge n_8_1 n_7_1)
		(edge n_8_1 n_9_1)
		(edge n_8_1 n_8_2)
		(edge n_8_1 n_8_0)
		(edge n_8_2 n_7_2)
		(edge n_8_2 n_9_2)
		(edge n_8_2 n_8_3)
		(edge n_8_2 n_8_1)
		(edge n_8_3 n_7_3)
		(edge n_8_3 n_9_3)
		(edge n_8_3 n_8_4)
		(edge n_8_3 n_8_2)
		(edge n_8_4 n_7_4)
		(edge n_8_4 n_9_4)
		(edge n_8_4 n_8_5)
		(edge n_8_4 n_8_3)
		(edge n_8_5 n_7_5)
		(edge n_8_5 n_9_5)
		(edge n_8_5 n_8_6)
		(edge n_8_5 n_8_4)
		(edge n_8_6 n_7_6)
		(edge n_8_6 n_9_6)
		(edge n_8_6 n_8_7)
		(edge n_8_6 n_8_5)
		(edge n_8_7 n_7_7)
		(edge n_8_7 n_9_7)
		(edge n_8_7 n_8_8)
		(edge n_8_7 n_8_6)
		(edge n_8_8 n_7_8)
		(edge n_8_8 n_9_8)
		(edge n_8_8 n_8_9)
		(edge n_8_8 n_8_7)
		(edge n_8_9 n_7_9)
		(edge n_8_9 n_9_9)
		(edge n_8_9 n_8_10)
		(edge n_8_9 n_8_8)
		(edge n_8_10 n_7_10)
		(edge n_8_10 n_9_10)
		(edge n_8_10 n_8_11)
		(edge n_8_10 n_8_9)
		(edge n_8_11 n_7_11)
		(edge n_8_11 n_9_11)
		(edge n_8_11 n_8_12)
		(edge n_8_11 n_8_10)
		(edge n_8_12 n_7_12)
		(edge n_8_12 n_9_12)
		(edge n_8_12 n_8_13)
		(edge n_8_12 n_8_11)
		(edge n_8_13 n_7_13)
		(edge n_8_13 n_9_13)
		(edge n_8_13 n_8_14)
		(edge n_8_13 n_8_12)
		(edge n_8_14 n_7_14)
		(edge n_8_14 n_9_14)
		(edge n_8_14 n_8_15)
		(edge n_8_14 n_8_13)
		(edge n_8_15 n_7_15)
		(edge n_8_15 n_9_15)
		(edge n_8_15 n_8_14)
		(edge n_9_0 n_8_0)
		(edge n_9_0 n_10_0)
		(edge n_9_0 n_9_1)
		(edge n_9_1 n_8_1)
		(edge n_9_1 n_10_1)
		(edge n_9_1 n_9_2)
		(edge n_9_1 n_9_0)
		(edge n_9_2 n_8_2)
		(edge n_9_2 n_10_2)
		(edge n_9_2 n_9_3)
		(edge n_9_2 n_9_1)
		(edge n_9_3 n_8_3)
		(edge n_9_3 n_10_3)
		(edge n_9_3 n_9_4)
		(edge n_9_3 n_9_2)
		(edge n_9_4 n_8_4)
		(edge n_9_4 n_10_4)
		(edge n_9_4 n_9_5)
		(edge n_9_4 n_9_3)
		(edge n_9_5 n_8_5)
		(edge n_9_5 n_10_5)
		(edge n_9_5 n_9_6)
		(edge n_9_5 n_9_4)
		(edge n_9_6 n_8_6)
		(edge n_9_6 n_10_6)
		(edge n_9_6 n_9_7)
		(edge n_9_6 n_9_5)
		(edge n_9_7 n_8_7)
		(edge n_9_7 n_10_7)
		(edge n_9_7 n_9_8)
		(edge n_9_7 n_9_6)
		(edge n_9_8 n_8_8)
		(edge n_9_8 n_10_8)
		(edge n_9_8 n_9_9)
		(edge n_9_8 n_9_7)
		(edge n_9_9 n_8_9)
		(edge n_9_9 n_10_9)
		(edge n_9_9 n_9_10)
		(edge n_9_9 n_9_8)
		(edge n_9_10 n_8_10)
		(edge n_9_10 n_10_10)
		(edge n_9_10 n_9_11)
		(edge n_9_10 n_9_9)
		(edge n_9_11 n_8_11)
		(edge n_9_11 n_10_11)
		(edge n_9_11 n_9_12)
		(edge n_9_11 n_9_10)
		(edge n_9_12 n_8_12)
		(edge n_9_12 n_10_12)
		(edge n_9_12 n_9_13)
		(edge n_9_12 n_9_11)
		(edge n_9_13 n_8_13)
		(edge n_9_13 n_10_13)
		(edge n_9_13 n_9_14)
		(edge n_9_13 n_9_12)
		(edge n_9_14 n_8_14)
		(edge n_9_14 n_10_14)
		(edge n_9_14 n_9_15)
		(edge n_9_14 n_9_13)
		(edge n_9_15 n_8_15)
		(edge n_9_15 n_10_15)
		(edge n_9_15 n_9_14)
		(edge n_10_0 n_9_0)
		(edge n_10_0 n_11_0)
		(edge n_10_0 n_10_1)
		(edge n_10_1 n_9_1)
		(edge n_10_1 n_11_1)
		(edge n_10_1 n_10_2)
		(edge n_10_1 n_10_0)
		(edge n_10_2 n_9_2)
		(edge n_10_2 n_11_2)
		(edge n_10_2 n_10_3)
		(edge n_10_2 n_10_1)
		(edge n_10_3 n_9_3)
		(edge n_10_3 n_11_3)
		(edge n_10_3 n_10_4)
		(edge n_10_3 n_10_2)
		(edge n_10_4 n_9_4)
		(edge n_10_4 n_11_4)
		(edge n_10_4 n_10_5)
		(edge n_10_4 n_10_3)
		(edge n_10_5 n_9_5)
		(edge n_10_5 n_11_5)
		(edge n_10_5 n_10_6)
		(edge n_10_5 n_10_4)
		(edge n_10_6 n_9_6)
		(edge n_10_6 n_11_6)
		(edge n_10_6 n_10_7)
		(edge n_10_6 n_10_5)
		(edge n_10_7 n_9_7)
		(edge n_10_7 n_11_7)
		(edge n_10_7 n_10_8)
		(edge n_10_7 n_10_6)
		(edge n_10_8 n_9_8)
		(edge n_10_8 n_11_8)
		(edge n_10_8 n_10_9)
		(edge n_10_8 n_10_7)
		(edge n_10_9 n_9_9)
		(edge n_10_9 n_11_9)
		(edge n_10_9 n_10_10)
		(edge n_10_9 n_10_8)
		(edge n_10_10 n_9_10)
		(edge n_10_10 n_11_10)
		(edge n_10_10 n_10_11)
		(edge n_10_10 n_10_9)
		(edge n_10_11 n_9_11)
		(edge n_10_11 n_11_11)
		(edge n_10_11 n_10_12)
		(edge n_10_11 n_10_10)
		(edge n_10_12 n_9_12)
		(edge n_10_12 n_11_12)
		(edge n_10_12 n_10_13)
		(edge n_10_12 n_10_11)
		(edge n_10_13 n_9_13)
		(edge n_10_13 n_11_13)
		(edge n_10_13 n_10_14)
		(edge n_10_13 n_10_12)
		(edge n_10_14 n_9_14)
		(edge n_10_14 n_11_14)
		(edge n_10_14 n_10_15)
		(edge n_10_14 n_10_13)
		(edge n_10_15 n_9_15)
		(edge n_10_15 n_11_15)
		(edge n_10_15 n_10_14)
		(edge n_11_0 n_10_0)
		(edge n_11_0 n_12_0)
		(edge n_11_0 n_11_1)
		(edge n_11_1 n_10_1)
		(edge n_11_1 n_12_1)
		(edge n_11_1 n_11_2)
		(edge n_11_1 n_11_0)
		(edge n_11_2 n_10_2)
		(edge n_11_2 n_12_2)
		(edge n_11_2 n_11_3)
		(edge n_11_2 n_11_1)
		(edge n_11_3 n_10_3)
		(edge n_11_3 n_12_3)
		(edge n_11_3 n_11_4)
		(edge n_11_3 n_11_2)
		(edge n_11_4 n_10_4)
		(edge n_11_4 n_12_4)
		(edge n_11_4 n_11_5)
		(edge n_11_4 n_11_3)
		(edge n_11_5 n_10_5)
		(edge n_11_5 n_12_5)
		(edge n_11_5 n_11_6)
		(edge n_11_5 n_11_4)
		(edge n_11_6 n_10_6)
		(edge n_11_6 n_12_6)
		(edge n_11_6 n_11_7)
		(edge n_11_6 n_11_5)
		(edge n_11_7 n_10_7)
		(edge n_11_7 n_12_7)
		(edge n_11_7 n_11_8)
		(edge n_11_7 n_11_6)
		(edge n_11_8 n_10_8)
		(edge n_11_8 n_12_8)
		(edge n_11_8 n_11_9)
		(edge n_11_8 n_11_7)
		(edge n_11_9 n_10_9)
		(edge n_11_9 n_12_9)
		(edge n_11_9 n_11_10)
		(edge n_11_9 n_11_8)
		(edge n_11_10 n_10_10)
		(edge n_11_10 n_12_10)
		(edge n_11_10 n_11_11)
		(edge n_11_10 n_11_9)
		(edge n_11_11 n_10_11)
		(edge n_11_11 n_12_11)
		(edge n_11_11 n_11_12)
		(edge n_11_11 n_11_10)
		(edge n_11_12 n_10_12)
		(edge n_11_12 n_12_12)
		(edge n_11_12 n_11_13)
		(edge n_11_12 n_11_11)
		(edge n_11_13 n_10_13)
		(edge n_11_13 n_12_13)
		(edge n_11_13 n_11_14)
		(edge n_11_13 n_11_12)
		(edge n_11_14 n_10_14)
		(edge n_11_14 n_12_14)
		(edge n_11_14 n_11_15)
		(edge n_11_14 n_11_13)
		(edge n_11_15 n_10_15)
		(edge n_11_15 n_12_15)
		(edge n_11_15 n_11_14)
		(edge n_12_0 n_11_0)
		(edge n_12_0 n_13_0)
		(edge n_12_0 n_12_1)
		(edge n_12_1 n_11_1)
		(edge n_12_1 n_13_1)
		(edge n_12_1 n_12_2)
		(edge n_12_1 n_12_0)
		(edge n_12_2 n_11_2)
		(edge n_12_2 n_13_2)
		(edge n_12_2 n_12_3)
		(edge n_12_2 n_12_1)
		(edge n_12_3 n_11_3)
		(edge n_12_3 n_13_3)
		(edge n_12_3 n_12_4)
		(edge n_12_3 n_12_2)
		(edge n_12_4 n_11_4)
		(edge n_12_4 n_13_4)
		(edge n_12_4 n_12_5)
		(edge n_12_4 n_12_3)
		(edge n_12_5 n_11_5)
		(edge n_12_5 n_13_5)
		(edge n_12_5 n_12_6)
		(edge n_12_5 n_12_4)
		(edge n_12_6 n_11_6)
		(edge n_12_6 n_13_6)
		(edge n_12_6 n_12_7)
		(edge n_12_6 n_12_5)
		(edge n_12_7 n_11_7)
		(edge n_12_7 n_13_7)
		(edge n_12_7 n_12_8)
		(edge n_12_7 n_12_6)
		(edge n_12_8 n_11_8)
		(edge n_12_8 n_13_8)
		(edge n_12_8 n_12_9)
		(edge n_12_8 n_12_7)
		(edge n_12_9 n_11_9)
		(edge n_12_9 n_13_9)
		(edge n_12_9 n_12_10)
		(edge n_12_9 n_12_8)
		(edge n_12_10 n_11_10)
		(edge n_12_10 n_13_10)
		(edge n_12_10 n_12_11)
		(edge n_12_10 n_12_9)
		(edge n_12_11 n_11_11)
		(edge n_12_11 n_13_11)
		(edge n_12_11 n_12_12)
		(edge n_12_11 n_12_10)
		(edge n_12_12 n_11_12)
		(edge n_12_12 n_13_12)
		(edge n_12_12 n_12_13)
		(edge n_12_12 n_12_11)
		(edge n_12_13 n_11_13)
		(edge n_12_13 n_13_13)
		(edge n_12_13 n_12_14)
		(edge n_12_13 n_12_12)
		(edge n_12_14 n_11_14)
		(edge n_12_14 n_13_14)
		(edge n_12_14 n_12_15)
		(edge n_12_14 n_12_13)
		(edge n_12_15 n_11_15)
		(edge n_12_15 n_13_15)
		(edge n_12_15 n_12_14)
		(edge n_13_0 n_12_0)
		(edge n_13_0 n_14_0)
		(edge n_13_0 n_13_1)
		(edge n_13_1 n_12_1)
		(edge n_13_1 n_14_1)
		(edge n_13_1 n_13_2)
		(edge n_13_1 n_13_0)
		(edge n_13_2 n_12_2)
		(edge n_13_2 n_14_2)
		(edge n_13_2 n_13_3)
		(edge n_13_2 n_13_1)
		(edge n_13_3 n_12_3)
		(edge n_13_3 n_14_3)
		(edge n_13_3 n_13_4)
		(edge n_13_3 n_13_2)
		(edge n_13_4 n_12_4)
		(edge n_13_4 n_14_4)
		(edge n_13_4 n_13_5)
		(edge n_13_4 n_13_3)
		(edge n_13_5 n_12_5)
		(edge n_13_5 n_14_5)
		(edge n_13_5 n_13_6)
		(edge n_13_5 n_13_4)
		(edge n_13_6 n_12_6)
		(edge n_13_6 n_14_6)
		(edge n_13_6 n_13_7)
		(edge n_13_6 n_13_5)
		(edge n_13_7 n_12_7)
		(edge n_13_7 n_14_7)
		(edge n_13_7 n_13_8)
		(edge n_13_7 n_13_6)
		(edge n_13_8 n_12_8)
		(edge n_13_8 n_14_8)
		(edge n_13_8 n_13_9)
		(edge n_13_8 n_13_7)
		(edge n_13_9 n_12_9)
		(edge n_13_9 n_14_9)
		(edge n_13_9 n_13_10)
		(edge n_13_9 n_13_8)
		(edge n_13_10 n_12_10)
		(edge n_13_10 n_14_10)
		(edge n_13_10 n_13_11)
		(edge n_13_10 n_13_9)
		(edge n_13_11 n_12_11)
		(edge n_13_11 n_14_11)
		(edge n_13_11 n_13_12)
		(edge n_13_11 n_13_10)
		(edge n_13_12 n_12_12)
		(edge n_13_12 n_14_12)
		(edge n_13_12 n_13_13)
		(edge n_13_12 n_13_11)
		(edge n_13_13 n_12_13)
		(edge n_13_13 n_14_13)
		(edge n_13_13 n_13_14)
		(edge n_13_13 n_13_12)
		(edge n_13_14 n_12_14)
		(edge n_13_14 n_14_14)
		(edge n_13_14 n_13_15)
		(edge n_13_14 n_13_13)
		(edge n_13_15 n_12_15)
		(edge n_13_15 n_14_15)
		(edge n_13_15 n_13_14)
		(edge n_14_0 n_13_0)
		(edge n_14_0 n_15_0)
		(edge n_14_0 n_14_1)
		(edge n_14_1 n_13_1)
		(edge n_14_1 n_15_1)
		(edge n_14_1 n_14_2)
		(edge n_14_1 n_14_0)
		(edge n_14_2 n_13_2)
		(edge n_14_2 n_15_2)
		(edge n_14_2 n_14_3)
		(edge n_14_2 n_14_1)
		(edge n_14_3 n_13_3)
		(edge n_14_3 n_15_3)
		(edge n_14_3 n_14_4)
		(edge n_14_3 n_14_2)
		(edge n_14_4 n_13_4)
		(edge n_14_4 n_15_4)
		(edge n_14_4 n_14_5)
		(edge n_14_4 n_14_3)
		(edge n_14_5 n_13_5)
		(edge n_14_5 n_15_5)
		(edge n_14_5 n_14_6)
		(edge n_14_5 n_14_4)
		(edge n_14_6 n_13_6)
		(edge n_14_6 n_15_6)
		(edge n_14_6 n_14_7)
		(edge n_14_6 n_14_5)
		(edge n_14_7 n_13_7)
		(edge n_14_7 n_15_7)
		(edge n_14_7 n_14_8)
		(edge n_14_7 n_14_6)
		(edge n_14_8 n_13_8)
		(edge n_14_8 n_15_8)
		(edge n_14_8 n_14_9)
		(edge n_14_8 n_14_7)
		(edge n_14_9 n_13_9)
		(edge n_14_9 n_15_9)
		(edge n_14_9 n_14_10)
		(edge n_14_9 n_14_8)
		(edge n_14_10 n_13_10)
		(edge n_14_10 n_15_10)
		(edge n_14_10 n_14_11)
		(edge n_14_10 n_14_9)
		(edge n_14_11 n_13_11)
		(edge n_14_11 n_15_11)
		(edge n_14_11 n_14_12)
		(edge n_14_11 n_14_10)
		(edge n_14_12 n_13_12)
		(edge n_14_12 n_15_12)
		(edge n_14_12 n_14_13)
		(edge n_14_12 n_14_11)
		(edge n_14_13 n_13_13)
		(edge n_14_13 n_15_13)
		(edge n_14_13 n_14_14)
		(edge n_14_13 n_14_12)
		(edge n_14_14 n_13_14)
		(edge n_14_14 n_15_14)
		(edge n_14_14 n_14_15)
		(edge n_14_14 n_14_13)
		(edge n_14_15 n_13_15)
		(edge n_14_15 n_15_15)
		(edge n_14_15 n_14_14)
		(edge n_15_0 n_14_0)
		(edge n_15_0 n_15_1)
		(edge n_15_1 n_14_1)
		(edge n_15_1 n_15_2)
		(edge n_15_1 n_15_0)
		(edge n_15_2 n_14_2)
		(edge n_15_2 n_15_3)
		(edge n_15_2 n_15_1)
		(edge n_15_3 n_14_3)
		(edge n_15_3 n_15_4)
		(edge n_15_3 n_15_2)
		(edge n_15_4 n_14_4)
		(edge n_15_4 n_15_5)
		(edge n_15_4 n_15_3)
		(edge n_15_5 n_14_5)
		(edge n_15_5 n_15_6)
		(edge n_15_5 n_15_4)
		(edge n_15_6 n_14_6)
		(edge n_15_6 n_15_7)
		(edge n_15_6 n_15_5)
		(edge n_15_7 n_14_7)
		(edge n_15_7 n_15_8)
		(edge n_15_7 n_15_6)
		(edge n_15_8 n_14_8)
		(edge n_15_8 n_15_9)
		(edge n_15_8 n_15_7)
		(edge n_15_9 n_14_9)
		(edge n_15_9 n_15_10)
		(edge n_15_9 n_15_8)
		(edge n_15_10 n_14_10)
		(edge n_15_10 n_15_11)
		(edge n_15_10 n_15_9)
		(edge n_15_11 n_14_11)
		(edge n_15_11 n_15_12)
		(edge n_15_11 n_15_10)
		(edge n_15_12 n_14_12)
		(edge n_15_12 n_15_13)
		(edge n_15_12 n_15_11)
		(edge n_15_13 n_14_13)
		(edge n_15_13 n_15_14)
		(edge n_15_13 n_15_12)
		(edge n_15_14 n_14_14)
		(edge n_15_14 n_15_15)
		(edge n_15_14 n_15_13)
		(edge n_15_15 n_14_15)
		(edge n_15_15 n_15_14)
    (= (location cat_0) n_12_13)
(= (location cat_1) n_8_2)
(= (location cat_2) n_1_14)
(= (location cat_3) n_1_7)
    (= (view_range cat_0) 2)
(= (view_range cat_1) 2)
(= (view_range cat_2) 2)
(= (view_range cat_3) 2)
   )

   (:goal
    (and
        (exit (location cat_0))
(exit (location cat_1))
(exit (location cat_2))
(exit (location cat_3))
    )
   )

   (:bounds
    (distance - int[0..1024])
   )

 )

