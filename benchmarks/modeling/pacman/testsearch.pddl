
(define (problem testsearch)
  (:domain pacman)
  (:objects
    testsearch - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) testsearch)
	(= (at the_pacman) 8)
	(= (collected) 0)
	(pellet_at 17)
	(pellet_at 7)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 2)
	)
  )

  

  (:bounds (location - int[1..25]) (score - int[0..2]))

  
)
