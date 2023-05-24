# Academic-Plan-Project--SPOT
The Registrar class is the main part of this project, which is responsible for managing the student's study plan and the user interface. 

In the constructor, the code creates a new GUI object and a new study plan object, and loads the catalog and rules. 

The `CreateRequiredAction()` function prompts the user to select an action and returns a pointer to a new action object based on the user's selection. The `ExecuteAction()` function executes the given action object and frees its memory. 

The `Run()` function runs an infinite loop that updates the user interface, creates and executes the required action objects. 

The `UpdateInterface()` function updates the user interface and draws the study plan. 

Overall, this project allows students to manage their courses and study plan through a graphical user interface.
