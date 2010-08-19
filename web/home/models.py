from django.db import models

from django.contrib.auth.models import User 
# Django's Admin interface - it's awesome.
from django.contrib import admin

Team = User

class TeamMember( models.Model ):
    team = models.ForeignKey( Team )
    name = models.CharField( max_length=100 )
    rollNumber = models.CharField( max_length=20 )

    class Admin:
        pass

