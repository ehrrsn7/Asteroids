from django.shortcuts import render

# firebase stuff
import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore

# helps us only initialize firestore once
global vars
vars = {}
vars["initialized"] = False

# firestore init process
def initialize_firestore():
    """
    Create database connection
    """

    # Use the application default credentials
    # ** GOOGLE_APPLICATION_CREDENTIALS defined on machine
    cred = credentials.ApplicationDefault() 
    if not vars["initialized"]:
        vars["initialized"] = True
        firebase_admin.initialize_app(cred, {
            'projectId': 'asteroids-high-scores',
        })

    # Get reference to database
    db = firestore.client()
    return db

def get_scores_doc(db):
    return db.collection("high-scores").document("scores")

def get_scores_dict(db):
    scores_doc = get_scores_doc(db)
    return scores_doc.get().to_dict()

def add_high_score(db):
    get_scores_doc(db) # .add(...)
    # todo: finish this


def sort_dict_by_value(d:dict):
    return sorted(d.items(), key=lambda x: x[1])

def get_high_scores(db):
    scores_dict = get_scores_dict(db)
    sort_dict_by_value(scores_dict)
    print(scores_dict)
    i = 0
    new_scores_dict = dict()
    for key, value in scores_dict.items():
        i += 1
        if i > 10: break
        print(i)
        new_scores_dict[key] = value
    return new_scores_dict


# Create your views here.

# game
def index(request):

    # connect to cloud
    db = initialize_firestore()

    # do things with cloud

    # define
    variables = {
        "title": "Asteroids",
        "width": 800,
        "height": 600,
        # pull from cloud:
        "high_scores": get_high_scores(db)
    }

    # load
    return render(request, 
        'asteroids/index.html', # display game html template
        variables               # send in information
    )

# main menu
def menu(request):

    # connect to cloud
    db = initialize_firestore()

    # define
    variables = {
        "title": "Asteroids",
        # pull from cloud:
        "high_scores": get_high_scores(db)
    }

    # load
    return render(request, 
        'asteroids/Main-Menu.html', # display main-menu html template
        variables                   # send in information
    )
