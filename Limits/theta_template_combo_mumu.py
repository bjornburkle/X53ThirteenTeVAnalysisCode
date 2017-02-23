

def getSSDLModel2016BD():
    model = build_model_from_rootfile('SSDLROOTFILE2016BD',include_mc_uncertainties=True)


    model.set_signal_processes('sig')
    
    procs = model.processes
    
    
    for proc in procs:
        
    #data driven
        if(proc=="FakeRate"):
            model.add_lognormal_uncertainty("FakeRate",math.log(1.50),proc)
        elif(proc=="ChargeMisID"):
            model.add_lognormal_uncertainty("ChargeMisIDUnc",math.log(1.25),proc)
    #background MC
        elif(proc!="FakeRate" and proc!='ChargeMisID' and proc!='sig'):
        #Common
            model.add_lognormal_uncertainty('pileup',math.log(1.06),proc)
            model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)
        #lepton ID
            model.add_lognormal_uncertainty('muIdSys',math.log(1.02),proc,'mumuBD')
        #lepton ISO
            model.add_lognormal_uncertainty('muIsoSys',math.log(1.02),proc,'mumuBD')
        #lepton Trig
            model.add_lognormal_uncertainty('LepTrig2016BD_mumu',math.log(1.03),proc,'mumuBD')
            
        #individual
            if(proc=='TTZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTW'):
                model.add_lognormal_uncertainty('MC',math.log(1.19),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTH'):
                model.add_lognormal_uncertainty('MC',math.log(1.30),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTTT'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.02),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.24),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='ZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.10),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.04),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WpWp'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WWZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='ZZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)

    #   signal
        else:
            model.add_lognormal_uncertainty('JetRes',math.log(1.01),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
            model.add_lognormal_uncertainty('PU',math.log(1.01),proc)
            model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)                                        
        #lepton ID
            model.add_lognormal_uncertainty('muIdSys',math.log(1.02),proc,'mumuBD')
        #lepton ISO
            model.add_lognormal_uncertainty('muIsoSys',math.log(1.02),proc,'mumuBD')
        #lepton Trig
            model.add_lognormal_uncertainty('LepTrig2016BD_mumu',math.log(1.03),proc,'mumuBD')


    return model


def getSSDLModel2016EH():
    model = build_model_from_rootfile('SSDLROOTFILE2016EH',include_mc_uncertainties=True)


    model.set_signal_processes('sig')
    
    procs = model.processes
    
    
    for proc in procs:
        
    #data driven
        if(proc=="FakeRate"):
            model.add_lognormal_uncertainty("FakeRate",math.log(1.50),proc)
        elif(proc=="ChargeMisID"):
            model.add_lognormal_uncertainty("ChargeMisIDUnc",math.log(1.25),proc)
    #background MC
        elif(proc!="FakeRate" and proc!='ChargeMisID' and proc!='sig'):
        #Common
            model.add_lognormal_uncertainty('pileup',math.log(1.06),proc)
            model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)
        #lepton ID
            model.add_lognormal_uncertainty('muIdSys',math.log(1.02),proc,'mumuEH')
        #lepton ISO
            model.add_lognormal_uncertainty('muIsoSys',math.log(1.02),proc,'mumuEH')
        #lepton Trig
            model.add_lognormal_uncertainty('LepTrig2016EH_mumu',math.log(1.03),proc,'mumuEH')
            
        #individual
            if(proc=='TTZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTW'):
                model.add_lognormal_uncertainty('MC',math.log(1.19),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTH'):
                model.add_lognormal_uncertainty('MC',math.log(1.30),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTTT'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.02),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.24),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='ZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.10),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.04),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WpWp'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WWZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='ZZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)

    #   signal
        else:
            model.add_lognormal_uncertainty('JetRes',math.log(1.01),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
            model.add_lognormal_uncertainty('PU',math.log(1.01),proc)
            model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)                                        
        #lepton ID
            model.add_lognormal_uncertainty('muIdSys',math.log(1.02),proc,'mumuEH')
        #lepton ISO
            model.add_lognormal_uncertainty('muIsoSys',math.log(1.02),proc,'mumuEH')
        #lepton Trig
            model.add_lognormal_uncertainty('LepTrig2016EH_mumu',math.log(1.03),proc,'mumuEH')


    return model

ssdlModel = getSSDLModel2016BD()
ssdlModel2= getSSDLModel2016EH()


ssdlModel.combine(ssdlModel2)
                                        
model_summary(ssdlModel)

#Bayesian Limits
plot_exp, plot_obs = bayesian_limits(ssdlModel,'all', n_toy = 5000, n_data = 500)

plot_exp.write_txt('EXPTXTFILE')
plot_obs.write_txt('OBSTXTFILE')

signal_process_groups = {'sig': ['sig']}
import json
f = open('JSONNAME_discovery.json', 'w')
disc = discovery(ssdlModel,use_data = False,input_expected='toys:XSEC',spid='sig',Z_error_max=0.1,ts_method=derll)
print disc
json.dump(disc, f)

#print "Asymptotic Limits:"
#print asymptotic_cls_limits(ssdlModel, signal_processes=[['sig']], beta_signal_expected=0.0, bootstrap_ssdlModel=True, input=None, n=1, options=None)

report.write_html('HTMLOUT')

