
(define (problem smallmaze-nc)
  (:domain pacman)
  (:objects
    smallmaze-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) smallmaze-nc)
	(= (at the_pacman) 78)
	(= (collected) 0)
	(pellet_at 178)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 1)
	)
  )

  

  (:bounds (location - int[1..220]) (score - int[0..1]))

  
)
