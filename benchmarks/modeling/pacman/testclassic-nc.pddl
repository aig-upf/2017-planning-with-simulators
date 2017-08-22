
(define (problem testclassic-nc)
  (:domain pacman)
  (:objects
    g0 - ghost
	testclassic-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) testclassic-nc)
	(= (at the_pacman) 42)
	(= (at g0) 13)
	(= (collected) 0)
	(pellet_at 34)
	(pellet_at 8)
	(pellet_at 12)
	(pellet_at 44)
	(pellet_at 14)
	(pellet_at 18)
	(pellet_at 22)
	(pellet_at 24)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 8)
	)
  )

  

  (:bounds (location - int[1..50]) (score - int[0..8]))

  
)
