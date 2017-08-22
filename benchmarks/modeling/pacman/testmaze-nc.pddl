
(define (problem testmaze-nc)
  (:domain pacman)
  (:objects
    testmaze-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) testmaze-nc)
	(= (at the_pacman) 19)
	(= (collected) 0)
	(pellet_at 12)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 1)
	)
  )

  

  (:bounds (location - int[1..30]) (score - int[0..1]))

  
)
