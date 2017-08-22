
(define (problem testsearch-nc)
  (:domain pacman)
  (:objects
    testsearch-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) testsearch-nc)
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
