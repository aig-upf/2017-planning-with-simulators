
(define (problem mediumsafesearch-nc)
  (:domain pacman)
  (:objects
    g0 - ghost
	mediumsafesearch-nc - layout
  )

  (:init
    (alive the_pacman)
	(= (map_layout) mediumsafesearch-nc)
	(= (at the_pacman) 140)
	(= (at g0) 47)
	(= (collected) 0)
	(pellet_at 130)
	(pellet_at 131)
	(pellet_at 132)
	(pellet_at 133)
	(pellet_at 134)
	(pellet_at 135)
	(pellet_at 136)
	(pellet_at 137)
	(pellet_at 138)
	(pellet_at 139)
	(pellet_at 142)
	(pellet_at 143)
	(pellet_at 144)
	(pellet_at 146)
	(pellet_at 147)
	(pellet_at 148)
	(pellet_at 149)
	(pellet_at 150)
	(pellet_at 151)
	(pellet_at 152)
	(pellet_at 153)
	(pellet_at 154)
	(pellet_at 33)
	(pellet_at 40)
	(pellet_at 41)
	(pellet_at 42)
	(pellet_at 43)
	(pellet_at 61)
	(pellet_at 64)
	(pellet_at 74)
	(pellet_at 92)
	(pellet_at 99)
	(pellet_at 105)
	(pellet_at 113)
	(pellet_at 117)
	(pellet_at 119)
	(pellet_at 123)
  )

  (:goal
    (and 
	(alive the_pacman)
	(= (collected) 37)
	)
  )

  

  (:bounds (location - int[1..186]) (score - int[0..37]))

  
)
