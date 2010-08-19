# Create your views here.

from django.shortcuts import render_to_response 
from django.template.context import RequestContext
from django.http import HttpResponse, HttpResponseRedirect
import django.contrib.auth as auth 
import django.contrib.auth.views as auth_views 
from web.home import models as home_models
import forms
import models

from web import settings

def manage(request):
    if request.POST:
        data = request.POST
        file_data = request.FILES
        sub = models.Submission(team = request.user)
        form = forms.SubmissionForm(data=data, files=file_data, instance=sub)
        if form.is_valid():
            form.save()
    else:
        form = forms.SubmissionForm()

    submissions = models.Submission.objects.filter(team = request.user)

    return render_to_response("manage.html", 
            {'form':form,
            'submissions':submissions},
            context_instance = RequestContext(request))

def standings(request):

    # Get the best bot for every team
    # TODO: Make query more efficient
    scores = {}
    bots = models.Submission.objects.all()
    for team in home_models.Team.objects.all():
        # Get bots' scores
        s = map( lambda t: t.score, bots.filter(team = team))
        if s:
            scores[team] = max(s)
    
    scores = scores.items()
    scores.sort(key=lambda ts: ts[1])
    scores = [ (p,) + s for (p,s) in zip(range(1,len(scores)+1), scores) ]
        
    return render_to_response("standings.html", 
            {'scores':scores},
            context_instance = RequestContext(request))

def results(request):
    return render_to_response("results.html", 
            {},
            context_instance = RequestContext(request))

