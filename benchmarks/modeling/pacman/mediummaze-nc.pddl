
(define (problem mediummaze-nc)
  (:domain pacman)
  (:objects
    mediummaze-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) mediummaze-nc)
	(= (at the_pacman) 71)
	(= (collected) 0)
	(pellet_at 578)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 1)
	)
  )

  

  (:bounds (location - int[1..648]) (score - int[0..1]))

  
)
