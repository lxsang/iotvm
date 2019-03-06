*Class UndefinedObject Object

Methods UndefinedObject 'all'
	isNil
		^ true
|
	notNil
		^ false
|
	printString
		^ 'nil'
|
	createGlobals	| aBlock str|
		" create global variables in initial image "
		true <- True new.
		false <- False new.
		smalltalk <- Smalltalk new.
		stdin <- (File new stdin).
		stdout <- (File new stdout).
		" create a dictionary of classes "
		classes <- Dictionary new.
		scheduler <- Scheduler new.
		symbols binaryDo: [:x :y | 
			(y class == Class)
				ifTrue: [ classes at: x put: y ] ].
		aBlock <- [
			systemProcess <- aBlock newProcess.
			scheduler run ].
		systemProcess <- aBlock newProcess.
	
|
	initialize
		" initialize the initial object image "
		self createGlobals.
]