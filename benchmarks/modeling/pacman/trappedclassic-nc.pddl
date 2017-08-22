
(define (problem trappedclassic-nc)
  (:domain pacman)
  (:objects
    g0 g1 - ghost
	trappedclassic-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) trappedclassic-nc)
	(= (at the_pacman) 13)
	(= (at g0) 18)
	(= (at g1) 15)
	(= (collected) 0)
	(pellet_at 26)
	(pellet_at 27)
	(pellet_at 28)
	(pellet_at 29)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 4)
	)
  )

  

  (:bounds (location - int[1..40]) (score - int[0..4]))

  
)
