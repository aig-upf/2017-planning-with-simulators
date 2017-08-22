(define (problem grid_4_2_4)
  (:domain predator_and_prey)
  (:objects
    prey_0 prey_1 prey_2 prey_3 - prey
    pred_0 pred_1 - predator
    n_0_0 n_0_1 n_0_2 n_0_3 n_1_0 n_1_1 n_1_2 n_1_3 n_2_0 n_2_1 n_2_2 n_2_3 n_3_0 n_3_1 n_3_2 n_3_3 - position
  )
  (:init
        (= (min_x) 0)
        (= (max_x) 3)
        (= (min_y) 0)
        (= (max_y) 3)

        	(= (x n_0_0) 0)
	(= (y n_0_0) 0)
	(= (x n_1_0) 0)
	(= (y n_1_0) 1)
	(= (x n_2_0) 0)
	(= (y n_2_0) 2)
	(= (x n_3_0) 0)
	(= (y n_3_0) 3)
	(= (x n_0_1) 1)
	(= (y n_0_1) 0)
	(= (x n_1_1) 1)
	(= (y n_1_1) 1)
	(= (x n_2_1) 1)
	(= (y n_2_1) 2)
	(= (x n_3_1) 1)
	(= (y n_3_1) 3)
	(= (x n_0_2) 2)
	(= (y n_0_2) 0)
	(= (x n_1_2) 2)
	(= (y n_1_2) 1)
	(= (x n_2_2) 2)
	(= (y n_2_2) 2)
	(= (x n_3_2) 2)
	(= (y n_3_2) 3)
	(= (x n_0_3) 3)
	(= (y n_0_3) 0)
	(= (x n_1_3) 3)
	(= (y n_1_3) 1)
	(= (x n_2_3) 3)
	(= (y n_2_3) 2)
	(= (x n_3_3) 3)
	(= (y n_3_3) 3)

        	(= (location prey_0) n_1_1)
	(= (location prey_1) n_2_3)
	(= (location prey_2) n_3_3)
	(= (location prey_3) n_0_1)

        (= (num_preds) 2)
        (= (current_slot) 0)

        (= (location pred_0) n_3_1)
(= (location pred_1) n_3_1)
        	(= (slot pred_0) 0)
	(= (slot pred_1) 1)

        	(= (dx pred_0) 0)
	(= (dx pred_1) 0)
        	(= (dy pred_0) 0)
	(= (dy pred_1) 0)
    )

   (:goal
        (and
            (@trapped (location prey_0))
(@trapped (location prey_1))
(@trapped (location prey_2))
(@trapped (location prey_3))
        )
   )

   (:bounds
    (coord - int[-1..4])
    (slot - int[0..2])
   )

 )

