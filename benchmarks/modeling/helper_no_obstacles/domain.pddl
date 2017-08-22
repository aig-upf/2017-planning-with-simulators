(define (domain helper_fn_strips)

    (:requirements :strips :typing :equality :adl)

    (:types
        ;; integer types:
        ;;  - distance between two nodes
        cat node - object
        distance - int
    )

    (:constants
        nowhere - node
    )

    (:predicates

        (blocked ?x - node) ;; whether node ?x is blocked

        (edge ?x ?y - node ) ;; whether there is an edge between x and y
        (exit ?x - node) ;; whether ?x is the exit node

        ;; whether there is light at a location
        (light ?x - node)

        ;; true when the cat can view a given node
        (@can_view ?c - cat ?n - node)
    )

    (:functions

        (location ?cat - cat) - node                ;; location of the cat

        ;; (cat_moves ?x) maps the node ?x into the node the cat
        ;; will move to, if the cat is already trapped, the returned
        ;; node is the constant 'nowhere'
        (@cat_moves ?v_range - distance ?x - node) - node
        (@distance_to_exit ?c - cat) - node

        ;; max distance the cat can see a light
        (view_range ?c - cat) - distance
    )

    ;; helper's actions
    (:action light_up
        :parameters (?n - node)
        :precondition (and (not (= ?n nowhere)) (not (light ?n)))
        :effect (and
            (light ?n)
            (forall (?c - cat) (assign (location ?c) (@cat_moves (view_range ?c) (location ?c))))
        )
    )

    (:action light_down
        :parameters (?n - node)
        :precondition (and (not (= ?n nowhere)) (light ?n))
        :effect (and
            (not (light ?n))
            (forall (?c - cat) (assign (location ?c) (@cat_moves (view_range ?c) (location ?c))))
        )
    )
)
