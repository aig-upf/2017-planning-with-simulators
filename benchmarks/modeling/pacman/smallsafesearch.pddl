
(define (problem smallsafesearch)
  (:domain pacman)
  (:objects
    g0 - ghost
	smallsafesearch - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) smallsafesearch)
	(= (at the_pacman) 119)
	(= (at g0) 16)
	(= (collected) 0)
	(pellet_at 116)
	(pellet_at 107)
	(pellet_at 11)
	(pellet_at 12)
	(pellet_at 125)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 5)
	)
  )

  

  (:bounds (location - int[1..135]) (score - int[0..5]))

  
)
