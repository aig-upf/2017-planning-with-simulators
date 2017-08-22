(define (domain predator_and_prey)

    (:requirements :strips :typing :equality :adl)

    (:types
        position animal - object
        predator prey - animal
        slot coord - int
    )

    (:constants
    )

    (:predicates
        (@trapped ?pos - position)
    )

    (:functions
        (dx ?o  - predator) - coord
        (dy ?o  - predator) - coord
        (@update ?p - position ?dx - coord ?dy - coord) - position
        (@next_move ?p - position ) - position
        (x ?p - position) - coord
        (y ?p - position) - coord
        (location ?a - animal) - position
        (min_x) - coord
        (max_x) - coord
        (min_y) - coord
        (max_y) - coord
        (slot ?p - predator) - slot
        (num_preds ) - slot
        (current_slot) - slot
        (@distance ?p1 - predator ?p2 - prey ) - coord
    )

    (:action stay_put
        :parameters (?p - predator)
        :precondition (and (= (current_slot) (slot ?p)))
        :effect (and
            (assign (dx ?p) 0)
            (assign (dy ?p) 0)
            (assign (current_slot) (+ (current_slot) 1))
        )
    )

    (:action move_up
        :parameters (?p - predator)
        :precondition (and (= (current_slot) (slot ?p)))
        :effect (and
            (assign (dx ?p) 0)
            (assign (dy ?p) -1)
            (assign (current_slot) (+ (current_slot) 1))
        )
    )

    (:action move_down
        :parameters (?p - predator)
        :precondition (and (= (current_slot) (slot ?p)))
        :effect (and
            (assign (dx ?p) 0)
            (assign (dy ?p) 1)
            (assign (current_slot) (+ (current_slot) 1))
        )
    )

    (:action move_left
        :parameters (?p - predator)
        :precondition (and (= (current_slot) (slot ?p)))
        :effect (and
            (assign (dx ?p) -1)
            (assign (dy ?p) 0)
            (assign (current_slot) (+ (current_slot) 1))
        )
    )

    (:action move_right
        :parameters (?p - predator)
        :precondition (and (= (current_slot) (slot ?p)))
        :effect (and
            (assign (dx ?p) 1)
            (assign (dy ?p) 0)
            (assign (current_slot) (+ (current_slot) 1))
        )
    )

    (:action simulate
        :parameters ()
        :precondition (and (= (current_slot) (num_preds)))
        :effect (and
            ;; NOTE: the parser messes up things by trying to "uniquify" variables,
            ;; over the effects, instead of leaving them alone it changes their names
            ;; but then doesn't remember to substitute the old variable name on the
            ;; effect...
            (forall (?p - predator) (assign (location ?p) (@update (location ?p) (dx ?p) (dy ?p))))
            (forall (?q - predator) (assign (dx ?q) 0))
            (forall (?r - predator) (assign (dy ?r) 0))
            (forall (?t - prey) (assign (location ?t) (@next_move (location ?t))))
            (assign (current_slot) 0)
        )
    )

)
