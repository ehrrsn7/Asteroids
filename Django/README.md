# Asteroids

Web Application using Python and the Django framework.

### Gameplay coming soon, I don't know how to host this game quite yet. When hosted, link will be posted [here].

My purpose in writing this software was mostly educational. I coded it for a class, as well as for my benefit. I mostly wanted to know how to work a front/back end website using a simple framework, as well as someday host and improve the site.

## \*[Demonstration Video](https://youtu.be/QeRJqTNZHQI)\* <br><br>

# Web Pages

Home - Landing page, very simple. Its purpose is to have buttons which are links which take you to any desired page within the app. Also, I plan on moving the high scores div here, or maybe to a new page. Whatever the case, I won't keep that div on the main game page.

Index - Page containing the Game.

# Development Environment

Used the Django Framework, powered by Python3.

Programmed using:
- Python (working with Django)
- HTML (with django template markup)
- CSS/JS (for site styles, gameplay, and event listeners)

# Useful Websites

### **Essentials:**
- Django first tutorial https://docs.djangoproject.com/en/3.1/intro/tutorial06/

- Using Django with Google Firebase
https://www.geeksforgeeks.org/how-to-create-a-new-project-in-django-using-firebase-database/

- Google Firestore query syntax guide/docs
https://cloud.google.com/firestore/docs/query-data/queries#python_3

### **Programming:**
#### **django**
- Figuring out how to only initialize the firebase connection once, I ended up needing a global variable to house a boolean keeping track of whether or not connection was initialized https://stackoverflow.com/questions/14420776/why-does-globalising-a-boolean-not-work-but-globalising-a-dictionary-does

- Figuring out how dbConnection.collection().doc().collection()'s return value is represented in django python https://stackoverflow.com/questions/49077425/firestore-documentsnapshot-to-python-dictionary

- can I use Django to get/work with front-end info? (no) (specifically referring to dynamically sizing game/window elements) https://stackoverflow.com/questions/5779570/get-screen-size-with-django-not-using-javascript


#### **python**
- python dictionary how-tos
    - https://stackoverflow.com/questions/7838142/display-dictionary-values-in-template
    - https://stackoverflow.com/questions/613183/how-do-i-sort-a-dictionary-by-value

- for high score: find max value in dict python https://www.kite.com/python/answers/how-to-find-the-max-value-in-a-dictionary-in-python 

#### **html/css/js**

- table styling https://www.w3schools.com/css/css_table.asp

#### **django html template markup**
- loading css/js from separate files in django html template 
    - https://stackoverflow.com/questions/48248832/stylesheet-not-loaded-because-of-mime-type
    - note: I ended up placing any css/js in /static instead of /template directory and using special django html template markup to call these files, as suggested by my professor. Example found [here.](https://docs.djangoproject.com/en/3.1/howto/static-files/)

- setting local vars in django template markup https://stackoverflow.com/questions/1070398/how-to-set-a-value-of-a-variable-inside-a-template-code

# Note to self:

\* From [medium.com](): \*

```
In terminal:
-- 
export GOOGLE_APPLICATION_CREDENTIALS='/path/to/credentials.json'
--
For my personal login to the firebase store. later, this will be done on the Server which I'll host this site on.
```

In browser: See the collection at https://console.firebase.google.com/u/0/project/asteroids-high-scores/firestore/data~2Fhigh-scores~2Fscores (invisible to public, pls don't hack meh)

# Future Work

* Host website, using Firebase? Pretty simple I guess, since I already used it for database storage for my high scores.
* Change high scores screen to be displayed on home page, only display one high score on index (game) page