(define (domain blocker_fn_strips)

    (:requirements :strips :typing :equality :adl)

    (:types
        cat node turn_token - object
        ;; integer types:
        ;;  - distance between two nodes
        distance - int
    )

    (:constants
        cats_turn blockers_turn - turn_token
        nowhere - node
    )

    (:predicates

        (blocked ?x - node) ;; whether node ?x is blocked

        (edge ?x ?y - node ) ;; whether there is an edge between x and y
        (exit ?x - node) ;; whether ?x is the exit node
        (@can_block ?n - node)
        (@trapped ?n - node) ;; true when the cat is at n and it is trapped
    )

    (:functions

        (current_turn) - turn_token ;; whose the current token
        (cat) - node                ;; location of the cat

        ;; (cat_moves ?x) maps the node ?x into the node the cat
        ;; will move to, if the cat is already trapped, the returned
        ;; node is the constant 'nowhere'
        (@cat_moves ?x - node) - node

        (@distance_to_exit ?x - node) - distance
    )

    ;; Blocker's action
    (:action block_1
        :parameters (?n - node)
        :precondition (and (= (current_turn) blockers_turn) (not (= ?n nowhere)) (edge ?n (cat)) (not (blocked ?n)))
        :effect (and
            (blocked ?n)
            (assign (current_turn) cats_turn)
        )
    )

    (:action block_2
        :parameters (?n - node)
        :precondition (and (= (current_turn) blockers_turn) (not (= ?n nowhere)) (edge (cat) ?n) (not (blocked ?n)))
        :effect (and
            (blocked ?n)
            (assign (current_turn) cats_turn)
        )
    )

     ;; Cat's action
     (:action move
        :parameters ()
        :precondition (and
            (= (current_turn) cats_turn)
        )
        :effect (and
            (assign (cat) (@cat_moves (cat)))
            (assign (current_turn) blockers_turn)
        )
     )

)
