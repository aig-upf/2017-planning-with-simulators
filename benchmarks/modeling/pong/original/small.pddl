(define (problem small)
  (:domain pong_fn_strips)
  (:objects
    p0 - puck
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

        ;; racket
        (= (center r0) 10)
        (= (radius r0) 3)
        (= (dy r0) 0)
        (= (prev_dy r0) 0)

        ;; puck initial conditions
        (= (x p0) 60)
        (= (y p0) 10)
        (= (v_vec p0) v_1_1)
        (= (acceleration p0) 1)

        ;; obstacles
        (= (hits r0_obs p0) 0)
        (= (hits top p0) 0)
        (= (hits bottom p0) 0)
        (= (hits right p0) 0)

        (= (bound top) 30)
        (= (bound bottom) 0)
        (= (bound right) 62)
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
            (> (hits r0_obs p0) 2)
        )
   )

   (:bounds
    (pixel - int[-192..192])
    (value - int[0..1000])
   )

 )
