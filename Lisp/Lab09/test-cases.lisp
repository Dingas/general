(deftest test-tr-delete ()
  (let ((trie (make-tr-node)))
    (tr-add "a" 11 trie)
    (tr-delete "a" trie)
    (check
     (tr-equal? trie #S(tr-node :val nil :children nil)))
    (tr-add "pie" 11 trie)
    (tr-delete "pie" trie)
    (check
     (tr-equal? trie #S(tr-node :val nil :children nil)))))

(deftest test-tr-count ()
  (let ((trie (make-tr-node)))
    (tr-add "peter" 1 trie)
    (tr-add "piper" 2 trie)
    (tr-add "picked" 3 trie)
    (tr-add "peck" 4 trie)
    (tr-add "pickled" 5 trie)
    (tr-add "peppers" 6 trie)
    (check
      (equal (tr-count trie) 6))))