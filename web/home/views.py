# Create your views here.

from django.shortcuts import render_to_response 
from django.template.context import RequestContext
from django.http import HttpResponse, HttpResponseRedirect

from web import settings

def home(request):
    return render_to_response("home.html", 
            context_instance = RequestContext(request))

