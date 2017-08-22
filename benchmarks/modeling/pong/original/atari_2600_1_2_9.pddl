(define (problem atari_2600)
  (:domain pong_fn_strips)
  (:objects
    p_0 - puck
  )
    (:init
        ;; velocity vectors data
        (= (vy v_0_0) 0)
        (= (vx v_0_0) 0)

        (= (vx v_1_0) 1)
        (= (vy v_1_0) 0)

        (= (vx v_m1_0) -1)
        (= (vy v_m1_0) 0)

        (= (vx v_0_1) 0)
        (= (vy v_0_1) 1)

        (= (vx v_0_m1) 0)
        (= (vy v_0_m1) -1)

        (= (vx v_1_1) 1)
        (= (vy v_1_1) 1)

        (= (vx v_1_m1) 1)
        (= (vy v_1_m1) -1)

        (= (vx v_m1_1) -1)
        (= (vy v_m1_1) 1)

        (= (vx v_m1_m1) -1)
        (= (vy v_m1_m1) -1)

        ;; paddle
        (= (center r0) 10)
        (= (radius r0) 5)
        (= (dy r0) 0)
        (= (prev_dy r0) 0)

        ;; puck initial conditions
        (= (x p_0) 47)
(= (y p_0) 15)
(= (v_vec p_0) v_1_1)
(= (acceleration p_0) 1)
(= (hits r0_obs p_0) 0)
(= (hits top p_0) 0)
(= (hits bottom p_0) 0)
(= (hits right p_0) 0)

        (= (bound top) 160)
        (= (bound bottom) 0)
        (= (bound right) 192)
        (= (bound r0_obs) 1)
        (= (bound left) 0)

        (= (check top) check_top)
        (= (check bottom) check_bottom)
        (= (check right) check_right)
        (= (check left) check_left)
        (= (check r0_obs) check_paddle)

        (= (next_mode control) sim_motion)
        (= (next_mode sim_motion) check_top)
        (= (next_mode check_top) check_bottom)
        (= (next_mode check_bottom) check_right)
        (= (next_mode check_right) check_paddle)
        (= (next_mode check_paddle) check_left)
        (= (next_mode check_left) control)

        (= (current_mode) control)
    )

   (:goal
       (and
           (@game_on)
           (> (hits r0_obs p_0) 2)
       )
   )

   (:bounds
    (pixel - int[-192..192])
    (value - int[0..1000])
   )

 )

