plugins {
    id("com.github.node-gradle.node") version "7.0.2"
}

node {
    download.set(true)
    version.set("20.10.0")
}

tasks {
    val npmInstall by existing

    // Task to run ESLint
    val lintJs by registering(com.github.node_gradle.node.npm.task.NpmTask::class) {
        dependsOn(npmInstall)
        group = "verification"
        args.set(listOf("run", "lint"))
        
        // Cache: don't re-run if src hasn't changed
        inputs.dir("src")
        outputs.upToDateWhen { true } 
    }

    // Task to run Jest tests
    val testJs by registering(com.github.node_gradle.node.npm.task.NpmTask::class) {
        dependsOn(npmInstall)
        group = "verification"
        args.set(listOf("run", "test"))
    }

    // Bind tasks to the standard Gradle 'check' lifecycle
    check {
        dependsOn(lintJs)
        dependsOn(testJs)
    }
}
