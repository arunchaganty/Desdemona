# Create your views here.

from django.shortcuts import render_to_response 
from django.template.context import RequestContext
from django.http import HttpResponse, HttpResponseRedirect
import django.contrib.auth as auth 
import django.contrib.auth.views as auth_views 
import forms
import models

from web import settings

def home(request):
    if request.POST:
        data = request.POST
        form = forms.LoginForm(data=data)
        if form.is_valid():
            auth.login(request, form.get_user())
    else:
        form = forms.LoginForm(None)
    return render_to_response("home.html", 
            {'form':form,},
            context_instance = RequestContext(request))

def register(request):
    if request.POST:
        data = request.POST
        form = forms.TeamRegistrationForm(data)
        if form.is_valid():
            team = models.Team.objects.create_user(
                    form.cleaned_data['name'], form.cleaned_data['email'], form.cleaned_data['password'])
            return HttpResponseRedirect('/home/')
    else:
        form = forms.TeamRegistrationForm(None)

    return render_to_response("register.html", 
            {'form':form,},
            context_instance = RequestContext(request))

def login(request):
    return home(request)

def logout(request):
    return auth.views.logout(request, '/home/')

# TODO:
def change_password(request):
    pass




