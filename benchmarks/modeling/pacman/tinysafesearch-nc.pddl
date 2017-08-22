
(define (problem tinysafesearch-nc)
  (:domain pacman)
  (:objects
    g0 - ghost
	tinysafesearch-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) tinysafesearch-nc)
	(= (at the_pacman) 29)
	(= (at g0) 12)
	(= (collected) 0)
	(pellet_at 38)
	(pellet_at 41)
	(pellet_at 44)
	(pellet_at 15)
	(pellet_at 47)
	(pellet_at 16)
	(pellet_at 50)
	(pellet_at 51)
	(pellet_at 52)
	(pellet_at 53)
	(pellet_at 17)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 11)
	)
  )

  

  (:bounds (location - int[1..63]) (score - int[0..11]))

  
)
