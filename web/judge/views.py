# Create your views here.

from django.shortcuts import render_to_response 
from django.template.context import RequestContext
from django.http import HttpResponse, HttpResponseRedirect
import django.contrib.auth as auth 
import django.contrib.auth.views as auth_views 
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

    return render_to_response("manage.html", 
            {'form':form},
            context_instance = RequestContext(request))

