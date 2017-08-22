
(define (problem trickysearch)
  (:domain pacman)
  (:objects
    trickysearch - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) trickysearch)
	(= (at the_pacman) 70)
	(= (collected) 0)
	(pellet_at 34)
	(pellet_at 35)
	(pellet_at 102)
	(pellet_at 103)
	(pellet_at 104)
	(pellet_at 105)
	(pellet_at 42)
	(pellet_at 106)
	(pellet_at 45)
	(pellet_at 48)
	(pellet_at 51)
	(pellet_at 22)
	(pellet_at 54)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 13)
	)
  )

  

  (:bounds (location - int[1..140]) (score - int[0..13]))

  
)
