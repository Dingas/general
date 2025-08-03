;;;; cps305-utils.asd

(asdf:defsystem #:cps305-utils
  :description "Describe cps305-utils here"
  :author "Your Name <your.name@example.com>"
  :license  "Specify license here"
  :version "0.0.1"
  :serial t
  :depends-on (#:rutils)
  :components ((:file "package")
               (:file "utils")
               (:file "lab01-test")
               (:file "lab02-test")
               (:file "lab03-test")
               (:file "lab04-test")
               (:file "lab05-test")
               (:file "lab06-test")
               (:file "lab07-test")
               (:file "lab08-test")
               (:file "lab09-test")
               (:file "cps305-utils")))
