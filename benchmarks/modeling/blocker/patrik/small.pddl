
;;     (0)
;;    / |
;; [1]-(2)
;;      |
;;     [3]

(define (problem four)
  (:domain blocker_fn_strips)

  (:objects n0 n1 n2 n3 - node)

  (:init (exit n1)
	 (exit n3)
	 (edge n0 n1)
	 (edge n0 n2)
	 (edge n1 n0)
	 (edge n1 n2)
	 (edge n2 n0)
	 (edge n2 n1)
	 (edge n2 n3)
	 (edge n3 n2)
	 (= (cat) n0)
	 (= (current_turn) blockers_turn)
	 )

  (:goal (and (@trapped (cat))))
  (:bounds (distance - int[0..5]))
  )
