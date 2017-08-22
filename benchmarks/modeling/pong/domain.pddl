(define (domain pong_fn_strips)

    (:requirements :strips :typing :equality :adl)

    (:types
        paddle puck mode velocity obstacle - object
        ;; integer types:
        ;;  - distance between two nodes
        pixel value - int
    )

    (:constants
        r0 - paddle
        control sim_motion check_top check_bottom check_right check_left check_paddle - mode
        ;; set of possible velocity vectors
        ;; (0,0), (0,1), ... (1,1), ..., (-1,-1)
        v_0_0 v_0_1 v_0_m1 v_1_0 v_m1_0 v_1_1 v_m1_1 v_1_m1 v_m1_m1 - velocity
        top bottom right left r0_obs - obstacle
    )

    (:predicates
        ;; true when the puck ?p collides with obstacle ?obs
        (@collision ?x - pixel ?y - pixel ?obs - obstacle)
        ;; true when there's no collision
        ;; (Temporary, negated axiomatic predicates are useful)
        (@not_collision ?x - pixel ?y - pixel ?obs - obstacle)
        ;; True when the game is on (i.e. at least one puck is unstuck)
        (@game_on)
    )

    (:functions
        (center ?r - paddle) - pixel ;; y-coordinate center of the paddle
        (radius ?r - paddle) - pixel ;; radius (in pixels) of the paddle

        (x ?p - puck) - pixel               ;; position of puck along x axis
        (y ?p - puck) - pixel               ;; position of puck along y axis
        (v_vec ?p - puck) - velocity        ;; velocity vector
        (vx ?v - velocity) - pixel          ;; velocity of puck along the x axis
        (vy ?v - velocity) - pixel          ;; velocity of puck along the y axis
        (acceleration ?p - puck) - pixel    ;; puck acceleration
        (dy ?r - paddle) - value            ;; velocity of paddle along the y axis
        (prev_dy ?r - paddle) - value       ;; used to remember the speed of the paddle
        (bound ?o - obstacle) - pixel       ;; all obstacles boundaries are described by lines

        (hits ?obs - obstacle ?p - puck) - value      ;; number of times puck has been hit with the paddle
        (current_mode) - mode               ;; mode of the game (control processing or simulation)
        (check ?o - obstacle) - mode        ;; check mode for obstacle
        (next_mode ?m - mode) - mode

        (@deflect ?obs - obstacle ?v - velocity) - velocity
        (@accelerate ?obs - obstacle ?a - pixel ?v - velocity) - pixel
        ;; keeps pixel p within interval [lb,ub]
        (@clamp ?x - pixel ?lb - pixel ?ub - pixel) - pixel
        ;; Features
        (@sum_hits) - value
        (@distance_to_paddle ?p - puck) - pixel
        (@get_puck_pixel ?p - puck) - value
    )


    (:action stop
        :parameters ()
        :precondition (and (@game_on) (= (current_mode) control) )
        :effect (and
            (assign (dy r0) 0)
            (assign (current_mode) (next_mode (current_mode)))
        )
    )

    (:action move_up
        :parameters ()
        :precondition (and (@game_on) (= (current_mode) control) (< (+ (center r0) (radius r0)) (bound top)) )
        :effect (and
            (assign (dy r0) 1)
            (assign (current_mode) (next_mode (current_mode)))
        )
    )

    (:action move_down
        :parameters ()
        :precondition (and (@game_on) (= (current_mode) control) (> (- (center r0) (radius r0)) (bound bottom)) )
        :effect (and
            (assign (dy r0) -1)
            (assign (current_mode) (next_mode (current_mode)))
        )
    )


    ;; uniformly accelerated motion (acceleration is constant!)
    (:action simulate_uam
        :parameters ()
        :precondition (and (@game_on) (= (current_mode) sim_motion))
        :effect (and
            (forall (?p - puck ) (assign (x ?p) (@clamp (+ (x ?p) (* (acceleration ?p) (vx (v_vec ?p)))) (bound left) (bound right))) )
            (forall (?q - puck ) (assign (y ?q) (@clamp (+ (y ?q) (* (acceleration ?q) (vy (v_vec ?q)))) (bound bottom) (bound top))) )
            (assign (center r0) (+ (center r0) (dy r0)))
            (assign (prev_dy r0) (dy r0))
            (assign (current_mode) (next_mode (current_mode)))
        )
    )

    (:action check_collision_1
        :parameters (?p - puck ?obs - obstacle)
        :precondition (and (@game_on) (= (current_mode) (check ?obs)) (@collision (x ?p) (y ?p) ?obs))
        :effect (and
            (assign (v_vec ?p) (@deflect ?obs (v_vec ?p)))
            ;; Deactivated - we cannot have zero crossings since actions are atomic!
            (assign (acceleration ?p) (@accelerate ?obs (acceleration ?p) (v_vec ?p)) )
            (assign (hits ?obs ?p) (+ (hits ?obs ?p) 1))
            (assign (current_mode) control)
        )
    )

    (:action check_collision_0
        :parameters (?p - puck ?obs - obstacle)
        :precondition (and (@game_on)  (= (current_mode) (check ?obs)) (@not_collision (x ?p) (y ?p) ?obs))
        :effect (and
            (assign (current_mode) (next_mode (current_mode)))
        )
    )
)
