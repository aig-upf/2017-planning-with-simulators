(:define
    (domain pacman)
    (:requirements :strips :typing :equality :adl)

    (:types
        locatable location pacman_mode - object
        cherry pill pacman ghost - locatable
        time slot - int
    )

    (:constants
        the_pacman - pacman
        the_cherry - cherry
        null - location
    )

    (:predicates
        (collected ?p - pill)
        (alive ?p - pacman)
        (active ?g - ghost)
        (edge ?p0 ?p1 - location)
    )

    (:functions
        (at ?o - locatable ) - location
        (@move_ghost ?g - ghost) - location
        (destination ?p - pacman) - location
        (super_mode) - time
    )

    (:action move
        :parameters (?b - location)
        :precondition (and  (alive the_pacman)
                            (edge (location the_pacman) ?b)
                            (not (= (location the_pacman) ?b))
                            (= (slot) 0))
        :effect (and
                        (assign (destination ?p) ?b)
                        (assign (slot) (+ (slot) 1))
                )
    )

    (:action update_ghosts
        :parameters ()
        :precondition   (and
                            (= (slot) 1)
                        )
        :effect (and
                        (forall (?g  - ghost) (when (active ?g) (assign (location ?g) (@move_ghost ?g))))
                        (assign (slot) (+ (slot) 1))
                )
    )

    (:action update_super_timer
        :parameters ()
        :precondition   (and
                            (> (super_mode) 0)
                            (= (slot) 2)
                        )
        :effect (and
                    (assign (super_mode) (- (super_mode) 1))
                    (assign (slot) (+ (slot) 1))
                )
    )

    (:action resolve
    :parameters ()
    :precondition   (and
                        (= (slot) 3)
                    )
    :effect (and
                (assign (location the_pacman) (destination the_pacman))
                (forall (?q - pill) (when (= (location ?q) (destination the_pacman)) (collected ?q)))
                (forall (?g - ghost) (when (and (> (super_mode) 0) (= (location ?g) (destination the_pacman))) (not (active ?g))))
                (forall (?g2 - ghost) (when (and (= (super_mode) 0) (= (location ?g2) (destination the_pacman))) (not (alive the_pacman))))
                (when   (and (= (super_mode) 0) (= (location the_cherry) (destination the_pacman)))
                        (and    (assign (location the_cherry) null)
                                (assign (super_mode) 30)
                        )
                )
                (assign (slot) 0)
            )
)
