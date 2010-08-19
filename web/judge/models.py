from django.db import models

from web.home import models as home_models

class Submission( models.Model ):
    team = models.ForeignKey( home_models.Team )
    timestamp = models.DateTimeField( auto_now = True )
    sha1sum = models.CharField( max_length=100 )
    data = models.FileField( upload_to='bots' )
    comments = models.TextField()

