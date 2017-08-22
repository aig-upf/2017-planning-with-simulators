
(define (problem smallsearch-nc)
  (:domain pacman)
  (:objects
    smallsearch-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) smallsearch-nc)
	(= (at the_pacman) 37)
	(= (collected) 0)
	(pellet_at 34)
	(pellet_at 67)
	(pellet_at 68)
	(pellet_at 69)
	(pellet_at 70)
	(pellet_at 71)
	(pellet_at 35)
	(pellet_at 36)
	(pellet_at 42)
	(pellet_at 39)
	(pellet_at 45)
	(pellet_at 79)
	(pellet_at 48)
	(pellet_at 51)
	(pellet_at 22)
	(pellet_at 54)
	(pellet_at 59)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 17)
	)
  )

  

  (:bounds (location - int[1..100]) (score - int[0..17]))

  
)
