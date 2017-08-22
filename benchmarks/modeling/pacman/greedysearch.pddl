
(define (problem greedysearch)
  (:domain pacman)
  (:objects
    greedysearch - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) greedysearch)
	(= (at the_pacman) 27)
	(= (collected) 0)
	(pellet_at 32)
	(pellet_at 38)
	(pellet_at 39)
	(pellet_at 8)
	(pellet_at 9)
	(pellet_at 40)
	(pellet_at 10)
	(pellet_at 41)
	(pellet_at 11)
	(pellet_at 17)
	(pellet_at 23)
	(pellet_at 26)
	(pellet_at 29)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 13)
	)
  )

  

  (:bounds (location - int[1..48]) (score - int[0..13]))

  
)
